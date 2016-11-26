#include "ordermanager.h"
#include <QDebug>

QList<TT_Subject*> *OrderManager::GetSubjects() const {
    return this->subjectsList; }

QList<TT_Teacher*> *OrderManager::GetTeachers() const {
    return this->teachersList; }

QList<TT_Classroom*> *OrderManager::GetClassrooms() const {
    return this->classroomsList; }

QList<TT_Week*> *OrderManager::GetWeeks() const {
    return this->weeksList; }


void OrderManager::Set(QList<TT_Subject *> *list) {
    this->subjectsList = list;
}

void OrderManager::Set(QList<TT_Teacher *> *list) {
    this->teachersList = list;
}

void OrderManager::Set(QList<TT_Classroom *> *list) {
    this->classroomsList = list;
}

void OrderManager::Set(QList<TT_Week *> *list) {
    this->weeksList = list;
    this->SetOrdersObjects();
}

void OrderManager::SetOrdersObjects() {
    for (int i = 0; i < this->weeksList->size(); ++i) {
        TT_Week *week = this->weeksList->at(i);
        QList<TT_Day*> *days = week->GetDays();
        for (int j = 0; j < days->size(); ++j) {
            TT_Day *day = days->at(j);
            QList<TT_Order*> *orders = day->GetOrders();
            for (int k = 0; k < orders->size(); ++k) {
                qOrders.append(orders->at(k));
                this->SetOrderObjects(orders->at(k));
            }
        }
    }
}

void OrderManager::SetOrderObjects(TT_Order *order) {
    int subjectId = order->GetSubjectId(), teacherId = order->GetTeacherId(), classroomId = order->GetClassroomId();

    if (subjectId > 0 && subjectId <= this->subjectsList->size())
        order->Set(this->subjectsList->at(subjectId - 1));
    else order->SetNulls(1, 0, 0);

    if (teacherId > 0 && teacherId <= this->teachersList->size())
        order->Set(this->teachersList->at(teacherId - 1));
    else order->SetNulls(0, 1, 0);

    if (classroomId > 0 && classroomId <= this->classroomsList->size())
        order->Set(this->classroomsList->at(classroomId - 1));
    else order->SetNulls(0, 0, 1);
}

void OrderManager::SetOrdersIds() {
    for (int i = 0; i < this->qOrders.size(); i++) {
        this->SetOrderIds(this->qOrders[i]);
    }
}

void OrderManager::SetOrderIds(TT_Order *order) {
    order->SetIds(order->GetSubject() ? (int)order->GetSubject()->GetId() : -1,
                  order->GetTeacher() ? (int)order->GetTeacher()->GetId() : -1,
                  order->GetClassroom() ? (int)order->GetClassroom()->GetId() : -1);
}

void OrderManager::Add(TT_Subject *subject) {
    int size = this->subjectsList->size();
    subject->SetId(size + 1);
    this->subjectsList->append(subject);
}

void OrderManager::Add(TT_Teacher *teacher) {
    int size = this->teachersList->size();
    teacher->SetId(size + 1);
    this->teachersList->append(teacher);
}

void OrderManager::Add(TT_Classroom *classroom) {
    int size = this->classroomsList->size();
    classroom->SetId(size + 1);
    this->classroomsList->append(classroom);
}

void OrderManager::Add(TT_Week *week) {
    int size = this->weeksList->size();
    week->SetId(size + 1);
    this->weeksList->append(week);

    QList<TT_Day*> *days = week->GetDays();
    for (int j = 0; j < days->size(); ++j) {
        TT_Day *day = days->at(j);
        QList<TT_Order*> *orders = day->GetOrders();
        for (int k = 0; k < orders->size(); ++k) {
            qOrders.append(orders->at(k));
            this->SetOrderObjects(orders->at(k));
        }
    }
}

void OrderManager::SetOrderNull(int index, bool s, bool t, bool c) {
    TT_Order *order = this->qOrders.at(index);
    order->SetNulls(s, t, c);
    order->SetIds(s ? 0 : -1,
                  t ? 0 : -1,
                  c ? 0 : -1);
}

void OrderManager::Remove(TT_Subject *subject) {
    // Delete this subject
    int id = subject->GetId(), i;
    TT_Subject *subject_it;
    for (i = 0; i < this->qOrders.size(); ++i) {
        int orderId = this->qOrders.at(i)->GetSubjectId();
        if (orderId == id) {
            this->SetOrderNull(i, 1);
        }
    }
    // Move list of subjects after "id" left
    for (i = id; i < this->subjectsList->size(); ++i) {
        subject_it = this->subjectsList->at(i);
        subject_it->SetId(subject_it->GetId() - 1);
    }
    this->SetOrdersIds();
    this->subjectsList->removeAt(id - 1);
    delete subject;
}

void OrderManager::Remove(TT_Teacher *teacher) {
    // Delete this subject
    int id = teacher->GetId(), i;
    TT_Teacher *teacher_it;
    for (i = 0; i < this->qOrders.size(); ++i) {
        int orderId = this->qOrders.at(i)->GetTeacherId();
        if (orderId == id) {
            this->SetOrderNull(i, 0, 1);
        }
    }
    // Move list of subjects after "id" left
    for (i = id; i < this->teachersList->size(); ++i) {
        teacher_it = this->teachersList->at(i);
        teacher_it->SetId(teacher_it->GetId() - 1);
    }
    this->SetOrdersIds();
    this->teachersList->removeAt(id - 1);
    delete teacher;
}

void OrderManager::Remove(TT_Classroom *classroom) {
    // Delete this subject
    int id = classroom->GetId(), i;
    TT_Classroom *classroom_it;
    for (i = 0; i < this->qOrders.size(); ++i) {
        int orderId = this->qOrders.at(i)->GetClassroomId();
        if (orderId == id) {
            this->SetOrderNull(i, 0, 0, 1);
        }
    }
    // Move list of subjects after "id" left
    for (i = id; i < this->classroomsList->size(); ++i) {
        classroom_it = this->classroomsList->at(i);
        classroom_it->SetId(classroom_it->GetId() - 1);
    }
    this->SetOrdersIds();
    this->classroomsList->removeAt(id - 1);
    delete classroom;
}

void OrderManager::Remove(TT_Week *week) {
    int id = week->GetId(), i;
    TT_Week *week_it;
    for (i = id; i < this->weeksList->size(); ++i) {
        week_it = this->weeksList->at(i);
        week_it->SetId(week_it->GetId() - 1);
    }
    for (int i = 0; i < this->weeksList->size(); ++i) {
        TT_Week *tWeek = this->weeksList->at(i);
        QList<TT_Day*> *days = tWeek->GetDays();
        for (int j = 0; j < days->size(); ++j) {
            TT_Day *day = days->at(j);
            QList<TT_Order*> *orders = day->GetOrders();
            for (int k = 0; k < orders->size(); ++k)
                qOrders.removeOne(orders->at(k));
        }
    }
    this->weeksList->removeAt(id - 1);
    delete week;
}

void OrderManager::Replace(TT_Subject *subject, TT_Subject *replacement) {
    int id = subject->GetId();
    replacement->SetId(id);
    this->subjectsList->replace(id - 1, replacement);
    delete subject;
    SetOrdersObjects();
}

void OrderManager::Replace(TT_Teacher *teacher, TT_Teacher *replacement) {
    int id = teacher->GetId();
    replacement->SetId(id);
    this->teachersList->replace(id - 1, replacement);
    delete teacher;
    SetOrdersObjects();
}

void OrderManager::Replace(TT_Classroom *classroom, TT_Classroom *replacement) {
    int id = classroom->GetId();
    replacement->SetId(id);
    this->classroomsList->replace(id - 1, replacement);
    delete classroom;
    SetOrdersObjects();
}
