#include "tt_teacher.h"

TT_Teacher::TT_Teacher() {}

TT_Teacher::TT_Teacher(QList<QString> name) {
    this->SetName(name);
}

void TT_Teacher::SetName(QList<QString> name) {
    int size = name.size();
    if (size > 0)
        this->name_1 = name[0].simplified();
    if (size > 1)
        this->name_2 = name[1].simplified();
    if (size > 2)
        this->name_3 = name[2].simplified();
}

QList<QString> TT_Teacher::GetName() const {
    QList<QString> name;
    name << this->name_1 << this->name_2 << this->name_3;
    return name;
}

QString TT_Teacher::GetLongName() const {
    return this->name_1 + " " + this->name_2 + " " + this->name_3;
}

QString TT_Teacher::GetShortName() const {
    return this->name_1 + " " + this->name_2.mid(0, 1) + ". " + this->name_3.mid(0, 1) + ".";
}

QJsonObject TT_Teacher::GetJSON() const {
    QJsonObject resultObject;
    QJsonArray name;
    name.append(this->name_1);
    name.append(this->name_2);
    name.append(this->name_3);
    resultObject["name"] = name;
    return resultObject;
}

void TT_Teacher::FromJSON(const QJsonObject *jsonObject) {
    QList<QString> nameList;
    QJsonArray name = (*jsonObject)["name"].toArray();
    nameList << name[0].toString() << name[1].toString() << name[2].toString();
    this->SetName(nameList);
}
