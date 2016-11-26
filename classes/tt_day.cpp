#include "tt_day.h"
#include <QDebug>

TT_Day::TT_Day() :orders(new QList<TT_Order*>) {}

QList<TT_Order*> *TT_Day::GetOrders() { return this->orders; }

QJsonArray TT_Day::GetJSON() const {
    QJsonArray resultObject;
    for (int i = 0; i < orders->size(); i++)
        resultObject.append(orders->at(i)->GetJSON());
    return resultObject;
}

void TT_Day::FromJSON(QJsonArray *jsonArray) {
    TT_Order *order;
    QJsonObject *jsonObject;
    foreach (const QJsonValue v, *jsonArray) {
        order = new TT_Order;
        jsonObject = new QJsonObject(v.toObject());
        order->SetIds((*jsonObject)["s"].toInt(),
                    (*jsonObject)["t"].toInt(),
                    (*jsonObject)["c"].toInt());
        this->orders->append(order);
    }
}
