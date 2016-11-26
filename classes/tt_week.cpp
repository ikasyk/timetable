#include "tt_week.h"

TT_Week::TT_Week() :days(new QList<TT_Day*>()) {
}

QList<TT_Day*>* TT_Week::GetDays() { return this->days; }

QJsonObject TT_Week::GetJSON() const {
    QJsonObject resultObject;
    QJsonArray daysArray;
    for (int i = 0; i < days->size(); ++i)
        daysArray.append(days->at(i)->GetJSON());
    resultObject["days"] = daysArray;
    return resultObject;
}

void TT_Week::FromJSON(const QJsonObject *jsonObject) {
    QJsonArray jsonArray = (*jsonObject)["days"].toArray();
    QJsonArray *obj;
    TT_Day *day;
    int i = 0;
    for (int i = 0; i < jsonArray.size(); i++) {
        day = new TT_Day;
        obj = new QJsonArray(jsonArray[i].toArray());
        day->FromJSON(obj);
        this->days->append(day);
    }
}
