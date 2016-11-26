#include <QCoreApplication>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include <QtAlgorithms>
#include <QPushButton>
#include <QApplication>
#include <QLabel>

#include "classes/initdata.h"
#include "classes/tt_subject.h"
#include "classes/tt_teacher.h"
#include "classes/tt_classroom.h"
#include "classes/tt_order.h"
#include "classes/tt_week.h"
#include "classes/datacontroller.h"
#include "classes/ordermanager.h"

#include "classes/ui_mainwindow.h"

#include <iostream>

int main(int argc, char *argv[]) {
    InitData::Instance().Open();

    QJsonDocument *Doc = InitData::Instance().GetDoc();
    QJsonObject Data = (*Doc).object();

    QList<TT_Subject*> *subjectsList = new QList<TT_Subject*>();
    DataController<TT_Subject> *subjectsController = new DataController<TT_Subject>(subjectsList);
    if (Data.find("subjects") != Data.end())
        subjectsController->FromJSON(Data["subjects"].toArray());

    QList<TT_Teacher*> *teachersList = new QList<TT_Teacher*>();
    DataController<TT_Teacher> *teachersController = new DataController<TT_Teacher>(teachersList);
    if (Data.find("teachers") != Data.end())
        teachersController->FromJSON(Data["teachers"].toArray());

    QList<TT_Classroom*> *classroomsList = new QList<TT_Classroom*>();
    DataController<TT_Classroom> *classroomsController = new DataController<TT_Classroom>(classroomsList);
    if (Data.find("classrooms") != Data.end())
        classroomsController->FromJSON(Data["classrooms"].toArray());

    QList<TT_Week*> *weeksList = new QList<TT_Week*>();
    DataController<TT_Week> *weeksController = new DataController<TT_Week>(weeksList);
    if (Data.find("loop") != Data.end())
        weeksController->FromJSON(Data["loop"].toArray());

    OrderManager::Instance().Set(subjectsList);
    OrderManager::Instance().Set(teachersList);
    OrderManager::Instance().Set(classroomsList);
    OrderManager::Instance().Set(weeksList);

    QApplication app(argc,argv);
    UI_MainWindow *MainWindow = new UI_MainWindow();
    MainWindow->show();

    return app.exec();
}
