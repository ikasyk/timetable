#ifndef TT_TEACHER_H
#define TT_TEACHER_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include "tt_item.h"

class TT_Teacher : public TT_Item {
    QString name_1, name_2, name_3;
public:
    TT_Teacher();
    TT_Teacher(QList<QString>);
    void SetName(QList<QString>);
    QList<QString> GetName() const;
    QString GetShortName() const;
    QString GetLongName() const;
    QJsonObject GetJSON() const;
    void FromJSON(const QJsonObject*);
};

#endif // TT_TEACHER_H
