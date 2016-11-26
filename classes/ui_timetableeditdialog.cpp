#include "ui_timetableeditdialog.h"

UI_TimetableEditDialog::UI_TimetableEditDialog(QWidget *parent) :QDialog(parent) {
    setWindowTitle(tr("Редагувати розклад"));
    resize(QSize(860, 600));
    setMinimumSize(800, 500);

    weeks = OrderManager::Instance().GetWeeks();

    QVBoxLayout *SubjectsLayout, *TeachersLayout, *ClassroomsLayout;

    SubjectsFilter = new QLineEdit;
    SubjectsFilter->setStyleSheet("padding: 3px;");
    SubjectsFilter->setPlaceholderText("Пошук предмета");
    connect(SubjectsFilter, SIGNAL(textChanged(const QString&)), this, SLOT(SubjectsByFilter(const QString&)));

    SubjectsCB = new UI_ItemDraggable;
    SubjectsCB->setIconSize(QSize(18, 18));

    SubjectsLayout = new QVBoxLayout;
    SubjectsLayout->addWidget(SubjectsFilter);
    SubjectsLayout->addWidget(SubjectsCB);

    TeachersFilter = new QLineEdit;
    TeachersFilter->setStyleSheet("padding: 3px;");
    TeachersFilter->setPlaceholderText("Пошук викладача");
    connect(TeachersFilter, SIGNAL(textChanged(const QString&)), this, SLOT(TeachersByFilter(const QString&)));

    TeachersCB = new UI_ItemDraggable;

    TeachersLayout = new QVBoxLayout;
    TeachersLayout->addWidget(TeachersFilter);
    TeachersLayout->addWidget(TeachersCB);

    ClassroomsFilter = new QLineEdit;
    ClassroomsFilter->setStyleSheet("padding: 3px;");
    ClassroomsFilter->setPlaceholderText("Пошук аудиторії");
    connect(ClassroomsFilter, SIGNAL(textChanged(const QString&)), this, SLOT(ClassroomsByFilter(const QString&)));

    ClassroomsCB = new UI_ItemDraggable;

    ClassroomsLayout = new QVBoxLayout;
    ClassroomsLayout->addWidget(ClassroomsFilter);
    ClassroomsLayout->addWidget(ClassroomsCB);

    MakeLists();

    TopLayout = new QHBoxLayout;
    TopLayout->addLayout(SubjectsLayout);
    TopLayout->addLayout(TeachersLayout);
    TopLayout->addLayout(ClassroomsLayout);

    QScrollArea *TT_Scroll = new QScrollArea;
    TT_Scroll->setObjectName("ttedit_scroll_area");
    TT_Scroll->setWidgetResizable(true);
    TT_Scroll->setStyleSheet("#ttedit_scroll_area { border: 0; }");

    TT_Layout = new QVBoxLayout;
    for (int i = 0; i < weeks->size(); i++)
        AddWeek(weeks->at(i));

    QWidget *TT_Wrap = new QWidget;
    TT_Wrap->setObjectName("tt_wrap");
    TT_Wrap->setStyleSheet("#tt_wrap { background: #FFF; }");
    TT_Wrap->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    TT_Wrap->setLayout(TT_Layout);
    TT_Scroll->setWidget(TT_Wrap);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    QPushButton *AddButton = new QPushButton("Додати тиждень");
    connect(AddButton, SIGNAL(clicked()), this, SLOT(AddButtonClick()));

    RemoveButton = new QPushButton("Видалити останній тиждень");
    connect(RemoveButton, SIGNAL(clicked()), this, SLOT(RemoveButtonClick()));
    buttonsLayout->addWidget(AddButton);
    buttonsLayout->addWidget(RemoveButton);
    RemoveWeekCheck();

    MainLayout = new QVBoxLayout;
    MainLayout->addLayout(TopLayout);
    MainLayout->addWidget(TT_Scroll);
    MainLayout->addLayout(buttonsLayout);
    setLayout(MainLayout);
}

void UI_TimetableEditDialog::AddWeek(int weekId) {
    QVBoxLayout *WeekLayout = new QVBoxLayout;
    if (!weekId) {
        TT_Week *newWeek = new TT_Week;
        newWeek->SetId(weeks->size() + 1);
        weeks->append(newWeek);
        weekId = weeks->size();
    }
    QStringList weekDays;
    weekDays << "Понеділок" << "Вівторок" << "Середа" << "Четвер" << "П'ятниця" << "Субота";

    QLabel *weekLabel = new QLabel(QString("<h3 align=\"center\">Тиждень %1</h3>").arg(weekId));
    UI_EditTable *table = new UI_EditTable(weeks->at(weekId - 1), this);
    table->setHorizontalHeaderLabels(weekDays);

    QPushButton *AddButton = new QPushButton("Додати пару");
    AddButton->setProperty("week", weekId);
    connect(AddButton, SIGNAL(clicked()), this, SLOT(AddPairClick()));

    WeekLayout->addWidget(weekLabel);
    WeekLayout->addWidget(table);
    WeekLayout->addWidget(AddButton);
    TT_Layout->addLayout(WeekLayout);

    tables.append(table);
}

void UI_TimetableEditDialog::AddWeek(TT_Week *week) {
    AddWeek(week->GetId());
    CompleteWeek(week);
}

void UI_TimetableEditDialog::CompleteWeek(TT_Week *week) {
    UI_EditTable *table = tables[week->GetId()-1];
    UI_TableItem *ti;
    TT_Order *to;
    int daysCount = week->GetDays()->size(), ordersCount, d, o;
    for (d = 0; d < daysCount; d++) {
        ordersCount = week->GetDays()->at(d)->GetOrders()->size();
        while (table->rowCount() < ordersCount) {
            AddPair(week->GetId());
        }
        for (o = 0; o < ordersCount; o++) {
            to = week->GetDays()->at(d)->GetOrders()->at(o);
            ti = new UI_TableItem;
            ti->setSubject(to->GetSubjectId());
            ti->setTeacher(to->GetTeacherId());
            ti->setClassroom(to->GetClassroomId());
            ti->setOrder(to);
            table->setCellWidget(o, d, ti);
        }
    }
}

void UI_TimetableEditDialog::RemoveWeek() {
    int id = weeks->size() - 1;
    weeks->pop_back();
    delete TT_Layout->takeAt(id);
}

void UI_TimetableEditDialog::RemoveWeekCheck() {
    RemoveButton->setDisabled(!weeks->size());
}

void UI_TimetableEditDialog::AddPair(int weekId) {
    UI_EditTable *table = tables[weekId - 1];
    table->insertRow( table->rowCount() );
    for (int j = 0; j < table->horizontalHeader()->count(); j++) {
        table->setCellWidget(table->rowCount()-1, j, new UI_TableItem);
    }
    table->updateHeight();
}

void UI_TimetableEditDialog::MakeLists() {
    MakeSubjects();
    MakeTeachers();
    MakeClassrooms();
}

void UI_TimetableEditDialog::MakeSubjects() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Subject*>* subjects = OrderManager::Instance().GetSubjects();
    QString subjectName;
    for (int i = 0; i < subjects->size(); i++) {
        subjectName = subjects->at(i)->GetName();
        if (subjectName.contains(SubjectsQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(subjectName, SubjectsCB);
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
            QJsonObject jsonObj;
            jsonObj["dt"] = 1;
            jsonObj["id"] = (int)subjects->at(i)->GetId();
            ListItem->setData(Qt::UserRole, QVariant(jsonObj));
        }
    }
}

void UI_TimetableEditDialog::MakeTeachers() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Teacher*>* teachers = OrderManager::Instance().GetTeachers();
    QString teacherName;
    for (int i = 0; i < teachers->size(); i++) {
        teacherName = teachers->at(i)->GetLongName();
        if (teacherName.contains(TeachersQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(teacherName, TeachersCB);
            QJsonObject jsonObj;
            jsonObj["dt"] = 2;
            jsonObj["id"] = (int)teachers->at(i)->GetId();
            ListItem->setData(Qt::UserRole, QVariant(jsonObj));
        }
    }
}

void UI_TimetableEditDialog::MakeClassrooms() {
    QListWidgetItem *ListItem = 0;
    QList<TT_Classroom*>* classrooms = OrderManager::Instance().GetClassrooms();
    QString classroomName;
    for (int i = 0; i < classrooms->size(); i++) {
        classroomName = classrooms->at(i)->GetFullRoom();
        if (classroomName.contains(ClassroomsQuery, Qt::CaseInsensitive)) {
            ListItem = new QListWidgetItem(classroomName, ClassroomsCB);
            QJsonObject jsonObj;
            jsonObj["dt"] = 3;
            jsonObj["id"] = (int)classrooms->at(i)->GetId();
            ListItem->setData(Qt::UserRole, QVariant(jsonObj));
        }
    }
}

void UI_TimetableEditDialog::AddButtonClick() {
    AddWeek();
    RemoveWeekCheck();
}

void UI_TimetableEditDialog::RemoveButtonClick() {
    RemoveWeek();
    RemoveWeekCheck();
}

void UI_TimetableEditDialog::AddPairClick() {
    int weekId = ((QPushButton*)sender())->property("week").toInt();
    AddPair(weekId);
}

void UI_TimetableEditDialog::SubjectsByFilter(const QString &query) {
    SubjectsQuery = query;
    SubjectsCB->clear();
    MakeSubjects();
}

void UI_TimetableEditDialog::TeachersByFilter(const QString &query) {
    TeachersQuery = query;
    TeachersCB->clear();
    MakeTeachers();
}

void UI_TimetableEditDialog::ClassroomsByFilter(const QString &query) {
    ClassroomsQuery = query;
    ClassroomsCB->clear();
    MakeClassrooms();
}

void UI_TimetableEditDialog::keyPressEvent(QKeyEvent *event) {
   if (event->key() != Qt::Key_Escape)
       QDialog::keyPressEvent(event);
}

void UI_TimetableEditDialog::reject() {
    this->Save();
    QDialog::reject();
    dynamic_cast<UI_MainWindow*>(parent())->RebuildTable();
}

void UI_TimetableEditDialog::Save() {
    OrderManager::Instance().SetOrdersObjects();
    InitData::Instance().Save();
}
