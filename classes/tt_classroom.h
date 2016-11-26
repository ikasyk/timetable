#ifndef TT_CLASSROOM_H
#define TT_CLASSROOM_H

#include <QString>
#include <QJsonObject>

#include "tt_item.h"

class TT_Classroom : public TT_Item {
    typedef unsigned short num;

    num corpus;
    QString room;
public:
    TT_Classroom();
    TT_Classroom(num, QString);
    void SetCorpus(num);
    num GetCorpus() const;
    void SetRoom(QString);
    QString GetRoom() const;
    QString GetFullRoom() const;
    QJsonObject GetJSON() const;
    void FromJSON(const QJsonObject*);
};

#endif // TT_CLASSROOM_H
