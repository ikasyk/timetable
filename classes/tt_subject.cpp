#include "tt_subject.h"

TT_Subject::TT_Subject() :name(QString("")) {
    this->SetType(1);
}

TT_Subject::TT_Subject(QString subject, unsigned t) :name(subject.simplified()) {
    this->SetType(t);
}

void TT_Subject::SetName(QString newName) {
    if (newName.size() != 0)
        this->name = newName.simplified();
}

QString TT_Subject::GetName() const {
    return name;
}

void TT_Subject::SetType(unsigned t) {
    if (t == 2 || t == 3)
        this->type = t;
    else
        this->type = 1;
}

unsigned TT_Subject::GetType() const {
    return this->type;
}

QJsonObject TT_Subject::GetJSON() const {
    QJsonObject resultObject;
    resultObject["type"] = (int)this->GetType();
    resultObject["name"] = this->GetName();
    return resultObject;
}

void TT_Subject::FromJSON(const QJsonObject *jsonObject) {
    this->SetName((*jsonObject)["name"].toString());
    this->SetType((*jsonObject)["type"].toInt());
}
