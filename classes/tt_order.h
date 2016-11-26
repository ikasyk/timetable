#ifndef TT_ORDER_H
#define TT_ORDER_H

#include "tt_subject.h"
#include "tt_teacher.h"
#include "tt_classroom.h"

class TT_Order : public TT_Item {
    TT_Subject *subject;
    TT_Teacher *teacher;
    TT_Classroom *classroom;
    int subjectId, teacherId, classroomId;
public:
    TT_Order();
    TT_Order(TT_Subject*, TT_Teacher*, TT_Classroom*);
    TT_Subject* GetSubject() const;
    TT_Teacher* GetTeacher() const;
    TT_Classroom* GetClassroom() const;
    int GetSubjectId() const;
    int GetTeacherId() const;
    int GetClassroomId() const;
    void Set(TT_Subject*);
    void Set(TT_Teacher*);
    void Set(TT_Classroom*);
    void SetIds(int = -1, int = -1, int = -1);
    void SetNulls(bool, bool, bool);
    QJsonObject GetJSON() const;
    void FromJSON(const QJsonObject*);
};

#endif // TT_ORDER_H
