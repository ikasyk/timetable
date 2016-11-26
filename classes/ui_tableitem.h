#ifndef UI_TABLEITEM_H
#define UI_TABLEITEM_H

#include <QtWidgets>
#include <QJsonObject>
#include "tt_week.h"
#include "tt_subject.h"
#include "tt_teacher.h"
#include "tt_classroom.h"
#include "ordermanager.h"

class UI_TableItem : public QWidget {
    Q_OBJECT
    TT_Order *order;
    QVBoxLayout *layout;
    QHBoxLayout *subjectLayout, *teacherLayout, *classroomLayout;
    QLabel *subjectLabel, *teacherLabel, *classroomLabel;
    int subject_id, teacher_id, classroom_id;
public:
    UI_TableItem(QWidget* = 0);
    void setSubject(int = 0);
    void setTeacher(int = 0);
    void setClassroom(int = 0);
    void setOrder(TT_Order*);
    QMenu *GetContextMenu();
public slots:
    void SlotDeleteSubject();
    void SlotDeleteTeacher();
    void SlotDeleteClassroom();
    void SlotDeleteAll();
};

#endif // UI_TABLEITEM_H
