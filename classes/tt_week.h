#ifndef TT_WEEK_H
#define TT_WEEK_H

#include <QList>
#include <QJsonArray>
#include "tt_day.h"
#include "tt_item.h"

/* This class need to debug!!!!!!! */

class TT_Week : public TT_Item {
    QList <TT_Day*> *days;
public:
    TT_Week();
    QList<TT_Day*>* GetDays();
    QJsonObject GetJSON() const;
    void FromJSON(const QJsonObject*);
};

#endif // TT_WEEK_H
