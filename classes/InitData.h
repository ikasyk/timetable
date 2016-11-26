#ifndef INITDATA_H
#define INITDATA_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "datacontroller.h"
#include "ordermanager.h"
#include "tt_subject.h"
#include "tt_teacher.h"
#include "tt_classroom.h"
#include "tt_order.h"

class InitData {
    QJsonDocument *docId;
public:
    static InitData &Instance() {
        static InitData _instance;
        return _instance;
    }
    bool Open();
    void Save();
    QJsonDocument *GetDoc();
private:
    InitData() {};
    InitData(const InitData &);
    InitData &operator = (InitData &);
};

#endif // INITDATA_H
