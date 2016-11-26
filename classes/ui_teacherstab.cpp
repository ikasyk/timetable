#include "ui_teacherstab.h"

UI_TeachersTab::UI_TeachersTab() :FilterQuery(tr("")) {
    QFont subjFont("Helvetica", 13);

    FilterWidget = new QLineEdit();
    FilterWidget->setStyleSheet("padding: 4px;");
    FilterWidget->setPlaceholderText("Пошук викладача");
    connect(FilterWidget, SIGNAL(textChanged(const QString&)), this, SLOT(MakeListByFilter(const QString&)));

    ListWidget = new QListWidget;
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

void UI_TeachersTab::MakeList() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Teacher*>* teachers = OrderManager::Instance().GetTeachers();
    QString teacherName;
    for (int i = 0; i < teachers->size(); i++) {
        teacherName = teachers->at(i)->GetLongName();
        if (teacherName.contains(FilterQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(teacherName, ListWidget);
            ListItem->setData(Qt::UserRole, QVariant((int)teachers->at(i)->GetId()));
        }
    }
}

void UI_TeachersTab::CheckButtons() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        EditButton->setDisabled(false);
        RemoveButton->setDisabled(false);
    } else {
        EditButton->setDisabled(true);
        RemoveButton->setDisabled(true);
    }
}

void UI_TeachersTab::AddButtonClicked() {
    UI_TeachersAddDialog *AddDialog = new UI_TeachersAddDialog(this);
    AddDialog->exec();
    delete AddDialog;

    InitData::Instance().Save();
    ListWidget->clear();
    MakeList();
}

void UI_TeachersTab::EditButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Teacher*>* Teachers = OrderManager::Instance().GetTeachers();
        UI_TeachersAddDialog *EditDialog = new UI_TeachersAddDialog(this, Teachers->at(index - 1));
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

void UI_TeachersTab::RemoveButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Teacher*>* teachers = OrderManager::Instance().GetTeachers();
        OrderManager::Instance().Remove(teachers->at(index - 1));

        InitData::Instance().Save();
        ListWidget->clear();
        MakeList();
        ListWidget->setCurrentItem(ListWidget->item(index > 1 ? index - 2 : index - 1));
        ListWidget->setFocus();
        CheckButtons();
    }
}

void UI_TeachersTab::CheckButtonsSlot() {
    CheckButtons();
}

void UI_TeachersTab::MakeListByFilter(const QString &text) {
    FilterQuery = text;
    ListWidget->clear();
    MakeList();
}

void UI_TeachersTab::ListItemClicked(QListWidgetItem *item) {
    EditButtonClicked();
}
