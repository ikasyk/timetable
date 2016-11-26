#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QList>

#include "tt_subject.h"
#include "tt_teacher.h"
#include "tt_classroom.h"
#include "tt_week.h"

class OrderManager {
    QList<TT_Subject*> *subjectsList;
    QList<TT_Teacher*> *teachersList;
    QList<TT_Classroom*> *classroomsList;
    QList<TT_Week*> *weeksList;
    QList<TT_Order*> qOrders;
public:
    QList<TT_Subject*> *GetSubjects() const;
    QList<TT_Teacher*> *GetTeachers() const;
    QList<TT_Classroom*> *GetClassrooms() const;
    QList<TT_Week*> *GetWeeks() const;
    void Set(QList<TT_Subject*> *);
    void Set(QList<TT_Teacher*> *);
    void Set(QList<TT_Classroom*> *);
    void Set(QList<TT_Week*> *);
    void SetOrdersObjects();
    void SetOrderObjects(TT_Order*);
    void SetOrdersIds();
    void SetOrderIds(TT_Order *order);
    void SetOrdersNull(bool=0, bool=0, bool=0);
    void SetOrderNull(int, bool=0, bool=0, bool=0);
    void Add(TT_Subject*);
    void Add(TT_Teacher*);
    void Add(TT_Classroom*);
    void Add(TT_Week*);
    void Remove(TT_Subject*);
    void Remove(TT_Teacher*);
    void Remove(TT_Classroom*);
    void Remove(TT_Week*);
    void Replace(TT_Subject*, TT_Subject*);
    void Replace(TT_Teacher*, TT_Teacher*);
    void Replace(TT_Classroom*, TT_Classroom*);
    void Replace(TT_Week*, TT_Week*);
    static OrderManager &Instance() {
        static OrderManager _instance;
        return _instance;
    }
private:
    OrderManager() {};
    OrderManager(const OrderManager &);
    OrderManager &operator = (OrderManager &);
};

#endif // ORDERMANAGER_H
