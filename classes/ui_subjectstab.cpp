#include "ui_subjectstab.h"

UI_SubjectsTab::UI_SubjectsTab() :FilterQuery(tr("")) {
    QFont subjFont("Helvetica", 13);

    FilterWidget = new QLineEdit();
    FilterWidget->setStyleSheet("padding: 4px;");
    FilterWidget->setPlaceholderText("Пошук предмету");
    connect(FilterWidget, SIGNAL(textChanged(const QString&)), this, SLOT(MakeListByFilter(const QString&)));

    ListWidget = new QListWidget;
    ListWidget->setIconSize(QSize(32, 32));
    ListWidget->setMaximumHeight(250);
    connect(ListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(CheckButtonsSlot()));
    connect(ListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ListItemClicked(QListWidgetItem*)));

    AddButton = new QPushButton("Додати");
    connect(AddButton, SIGNAL(clicked()), this, SLOT(AddButtonClicked()));

    EditButton = new QPushButton("Змінити");
    connect(EditButton, SIGNAL(clicked()), this, SLOT(EditButtonClicked()));

    RemoveButton = new QPushButton("Видалити");
    connect(RemoveButton, SIGNAL(clicked()), this, SLOT(RemoveButtonClicked()));

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout->addWidget(AddButton);
    ButtonsLayout->addWidget(EditButton);
    ButtonsLayout->addWidget(RemoveButton);

    QVBoxLayout *MainLayout = new QVBoxLayout;
    MainLayout->setMargin(15);
    MainLayout->setSpacing(5);
    MainLayout->addWidget(FilterWidget);
    MainLayout->addWidget(ListWidget);
    MainLayout->addLayout(ButtonsLayout);
    setLayout(MainLayout);

    MakeList();
    CheckButtons();
}

void UI_SubjectsTab::MakeList() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Subject*>* subjects = OrderManager::Instance().GetSubjects();
    QString subjectName;
    for (int i = 0; i < subjects->size(); i++) {
        subjectName = subjects->at(i)->GetName();
        if (subjectName.contains(FilterQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(subjectName, ListWidget);
            switch (subjects->at(i)->GetType()) {
            case 1:
                ListItem->setIcon(QPixmap("://images/lecture.png"));
                break;
            case 2:
                ListItem->setIcon(QPixmap("://images/practice.png"));
                break;
            case 3:
                ListItem->setIcon(QPixmap("://images/laboratory.png"));
                break;
            }
            ListItem->setData(Qt::UserRole, QVariant((int)subjects->at(i)->GetId()));
        }
    }
    CheckButtons();
}

void UI_SubjectsTab::CheckButtons() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        EditButton->setDisabled(false);
        RemoveButton->setDisabled(false);
    } else {
        EditButton->setDisabled(true);
        RemoveButton->setDisabled(true);
    }
}

void UI_SubjectsTab::AddButtonClicked() {
    UI_SubjectsAddDialog *AddDialog = new UI_SubjectsAddDialog(this);
    AddDialog->exec();
    delete AddDialog;

    InitData::Instance().Save();
    ListWidget->clear();
    MakeList();
}

void UI_SubjectsTab::EditButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Subject*>* subjects = OrderManager::Instance().GetSubjects();
        UI_SubjectsAddDialog *EditDialog = new UI_SubjectsAddDialog(this, subjects->at(index - 1));
        EditDialog->exec();
        delete EditDialog;

        InitData::Instance().Save();
        ListWidget->clear();
        MakeList();
        ListWidget->setCurrentItem(ListWidget->item(index - 1));
        ListWidget->setFocus();
        CheckButtons();
    }
}

void UI_SubjectsTab::RemoveButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Subject*>* subjects = OrderManager::Instance().GetSubjects();
        OrderManager::Instance().Remove(subjects->at(index - 1));

        InitData::Instance().Save();
        ListWidget->clear();
        MakeList();
        ListWidget->setCurrentItem(ListWidget->item(index > 1 ? index - 2 : index - 1));
        ListWidget->setFocus();
        CheckButtons();
    }
}

void UI_SubjectsTab::CheckButtonsSlot() {
    CheckButtons();
}

void UI_SubjectsTab::MakeListByFilter(const QString &text) {
    FilterQuery = text;
    ListWidget->clear();
    MakeList();
}

void UI_SubjectsTab::ListItemClicked(QListWidgetItem *item) {
    EditButtonClicked();
}
