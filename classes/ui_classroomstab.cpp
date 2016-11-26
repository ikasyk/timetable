#include "ui_classroomstab.h"

UI_ClassroomsTab::UI_ClassroomsTab() {
    FilterWidget = new QLineEdit();
    FilterWidget->setStyleSheet("padding: 4px;");
    FilterWidget->setPlaceholderText("Пошук аудиторії");
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

void UI_ClassroomsTab::MakeList() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Classroom*>* classrooms = OrderManager::Instance().GetClassrooms();
    QString classroomName;
    for (int i = 0; i < classrooms->size(); i++) {
        classroomName = classrooms->at(i)->GetFullRoom();
        if (classroomName.contains(FilterQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(classroomName, ListWidget);
            ListItem->setData(Qt::UserRole, QVariant((int)classrooms->at(i)->GetId()));
        }
    }
    //ListWidget->setCurrentItem(ListWidget->item(0));
}

void UI_ClassroomsTab::CheckButtons() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        EditButton->setDisabled(false);
        RemoveButton->setDisabled(false);
    } else {
        EditButton->setDisabled(true);
        RemoveButton->setDisabled(true);
    }
}

void UI_ClassroomsTab::AddButtonClicked() {
    UI_ClassroomsAddDialog *AddDialog = new UI_ClassroomsAddDialog(this);
    AddDialog->exec();
    delete AddDialog;

    InitData::Instance().Save();
    ListWidget->clear();
    MakeList();
}

void UI_ClassroomsTab::EditButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Classroom*>* Classrooms = OrderManager::Instance().GetClassrooms();
        UI_ClassroomsAddDialog *EditDialog = new UI_ClassroomsAddDialog(this, Classrooms->at(index - 1));
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

void UI_ClassroomsTab::RemoveButtonClicked() {
    QListWidgetItem *currentItem = ListWidget->currentItem();
    if (currentItem) {
        int index = ListWidget->currentItem()->data(Qt::UserRole).toInt();
        QList<TT_Classroom*>* classrooms = OrderManager::Instance().GetClassrooms();
        OrderManager::Instance().Remove(classrooms->at(index - 1));

        InitData::Instance().Save();
        ListWidget->clear();
        MakeList();
        ListWidget->setCurrentItem(ListWidget->item(index > 1 ? index - 2 : index - 1));
        ListWidget->setFocus();
        CheckButtons();
    }
}

void UI_ClassroomsTab::CheckButtonsSlot() {
    CheckButtons();
}

void UI_ClassroomsTab::MakeListByFilter(const QString &text) {
    FilterQuery = text;
    ListWidget->clear();
    MakeList();
}

void UI_ClassroomsTab::ListItemClicked(QListWidgetItem *) {
   EditButtonClicked();
}
