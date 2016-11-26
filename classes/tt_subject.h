#ifndef TT_SUBJECT_H
#define TT_SUBJECT_H

#include <QString>
#include <QJsonObject>

#include "tt_item.h"

class TT_Subject : public TT_Item {
    QString name;
    int type;
public:
    TT_Subject();
    TT_Subject(QString, unsigned);
    void SetName(QString);
    QString GetName() const;
    void SetType(unsigned);
    unsigned GetType() const;
    QJsonObject GetJSON() const;
    void FromJSON(const QJsonObject*);
};

#endif // TT_SUBJECT_H
