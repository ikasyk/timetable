#include "tt_classroom.h"

TT_Classroom::TT_Classroom() :corpus(0), room("") { }

TT_Classroom::TT_Classroom(TT_Classroom::num c, QString r) :corpus(c), room(r.simplified()) {}

TT_Classroom::num TT_Classroom::GetCorpus() const { return this->corpus; }
QString TT_Classroom::GetRoom() const { return this->room; }

void TT_Classroom::SetCorpus(TT_Classroom::num c) {
    this->corpus = c;
}

void TT_Classroom::SetRoom(QString r) {
    this->room = r.simplified();
}

QString TT_Classroom::GetFullRoom() const {
    return QString(GetRoom()) + "-" + QString::number(GetCorpus());
}

QJsonObject TT_Classroom::GetJSON() const {
    QJsonObject resultObject;
    resultObject["corpus"] = this->corpus;
    resultObject["room"] = this->room;
    return resultObject;
}

void TT_Classroom::FromJSON(const QJsonObject *jsonObject) {
    this->SetCorpus((*jsonObject)["corpus"].toInt());
    this->SetRoom((*jsonObject)["room"].toString());
}
