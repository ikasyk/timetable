#include "tt_order.h"
#include <QDebug>

TT_Order::TT_Order() :subject(NULL), teacher(NULL), classroom(NULL), subjectId(0), teacherId(0), classroomId(0) {}

TT_Order::TT_Order(TT_Subject *s, TT_Teacher *t, TT_Classroom *c)
    :subject(s), teacher(t), classroom(c), subjectId(0), teacherId(0), classroomId(0) {}

TT_Subject* TT_Order::GetSubject() const { return this->subject; }
TT_Teacher* TT_Order::GetTeacher() const { return this->teacher; }
TT_Classroom* TT_Order::GetClassroom() const { return this->classroom; }
int TT_Order::GetSubjectId() const { return this->subjectId; }
int TT_Order::GetTeacherId() const { return this->teacherId; }
int TT_Order::GetClassroomId() const { return this->classroomId; }

void TT_Order::Set(TT_Subject *s) { this->subject = s; }
void TT_Order::Set(TT_Teacher *t) { this->teacher = t; }
void TT_Order::Set(TT_Classroom *c) { this->classroom = c; }

QJsonObject TT_Order::GetJSON() const {
    QJsonObject resultObject;
    resultObject["s"] = this->GetSubject() ? (int)this->GetSubject()->GetId() : 0;
    resultObject["t"] = this->GetTeacher() ? (int)this->GetTeacher()->GetId() : 0;
    resultObject["c"] = this->GetClassroom() ? (int)this->GetClassroom()->GetId() : 0;
    return resultObject;
}

void TT_Order::FromJSON(const QJsonObject *jsonObject) {
    SetIds((*jsonObject)["s"].toInt(),
            (*jsonObject)["t"].toInt(),
            (*jsonObject)["c"].toInt() );
}

void TT_Order::SetIds(int s, int t, int c) {
    if (s >= 0) this->subjectId = s;
    if (t >= 0) this->teacherId = t;
    if (c >= 0) this->classroomId = c;
}

void TT_Order::SetNulls(bool s, bool t, bool c) {
    //printf("%b %b %b", s, t ,c);
    if (s)
        this->subject = NULL;
    if (t)
        this->teacher = NULL;
    if (c)
        this->classroom = NULL;
}
