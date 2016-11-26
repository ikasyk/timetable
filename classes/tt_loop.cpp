#include "tt_loop.h"

TT_Loop::TT_Loop() :weeks(new QList<TT_Week*>()) {}

QList<TT_Week*>* TT_Loop::GetWeeks() { return this->weeks; }

QJsonObject TT_Loop::GetJSON() const {
    QJsonObject resultObject;
    QJsonArray weeksArray;
    for (int i = 0; i < weeks->size(); ++i)
        weeksArray.append(weeks->at(i)->GetJSON());
    resultObject["weeks"] = weeksArray;
    return resultObject;
}

void TT_Loop::FromJSON(const QJsonObject *jsonObject) {
    QJsonArray jsonArray = (*jsonObject)["weeks"].toArray();
    QJsonObject *obj;
    int i = 0;
    foreach (const QJsonValue v, jsonArray) {
        obj = new QJsonObject(v.toObject());
        this->weeks->at(i++)->FromJSON(obj);
    }
}
