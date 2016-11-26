#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QDebug>

template <class T> class DataController {
    QList <T*> *data;
public:
    DataController(QList<T*> *d):data(d){};

    QJsonArray GetJSON() {
        QJsonArray resultArray;
        for (auto it: *data) {
            resultArray.insert(resultArray.end(), (*it).GetJSON());
        }
        return resultArray;
    };

    void FromJSON(QJsonArray dataArray) {
        T *op;

        unsigned long o_id = 0;
        foreach (const QJsonValue value, dataArray) {
            ++o_id;
            op = new T();
            QJsonObject *obj = new QJsonObject(value.toObject());
            op->SetId(o_id);
            op->FromJSON(obj);
            data->push_back(op);
        }
    };

};


#endif // DATACONTROLLER_H
