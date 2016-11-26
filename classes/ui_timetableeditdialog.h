#ifndef UI_TIMETABLEEDITDIALOG_H
#define UI_TIMETABLEEDITDIALOG_H

#include <QtWidgets>
#include "ordermanager.h"
#include "tt_week.h"
#include "ui_edittable.h"
#include "ui_itemdraggable.h"
#include "initdata.h"
#include "ui_mainwindow.h"

class UI_TimetableEditDialog : public QDialog {
    Q_OBJECT
    QList<TT_Week*> *weeks;
    QVBoxLayout *MainLayout, *TT_Layout;
    QHBoxLayout *TopLayout;
    QWidget *MainWidget;
    QLineEdit *SubjectsFilter, *TeachersFilter, *ClassroomsFilter;
    QListWidget *SubjectsCB, *TeachersCB, *ClassroomsCB;
    QList<UI_EditTable*> tables;
    QString SubjectsQuery, TeachersQuery, ClassroomsQuery;
    QPushButton *RemoveButton;
    void CompleteWeek(TT_Week*);
public:
    UI_TimetableEditDialog(QWidget* = 0);
    void AddWeek(int = 0);
    void AddWeek(TT_Week*);
    void RemoveWeek();
    void RemoveWeekCheck();
    void AddPair(int = 0);
    void MakeLists();
    void MakeSubjects();
    void MakeTeachers();
    void MakeClassrooms();
    virtual void reject();
    virtual void keyPressEvent(QKeyEvent *);
    void Save();
public slots:
    void AddButtonClick();
    void RemoveButtonClick();
    void AddPairClick();
    void SubjectsByFilter(const QString&);
    void TeachersByFilter(const QString&);
    void ClassroomsByFilter(const QString&);
};

#endif // UI_TIMETABLEEDITDIALOG_H
