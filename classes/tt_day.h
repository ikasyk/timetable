#ifndef TT_DAY_H
#define TT_DAY_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "tt_order.h"

class TT_Day {
    QList <TT_Order*> *orders;
public:
    TT_Day();
    QList<TT_Order*>* GetOrders();
    QJsonArray GetJSON() const;
    void FromJSON(QJsonArray*);
};

#endif // TT_DAY_H
