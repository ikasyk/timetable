#include "initdata.h"

bool InitData::Open() {
    QFile fileId(QString("timetable.json"));

    if (!fileId.open(QIODevice::ReadOnly)) {
        this->docId = new QJsonDocument();
        printf("Data file not found.\n");
        return false;
    }

    QByteArray readData = fileId.readAll();

    this->docId = new QJsonDocument(QJsonDocument::fromJson(readData));

    return true;
}

void InitData::Save() {
    QJsonObject Doc;
    Doc["subjects"] = (new DataController<TT_Subject>(OrderManager::Instance().GetSubjects()))->GetJSON();
    Doc["teachers"] = (new DataController<TT_Teacher>(OrderManager::Instance().GetTeachers()))->GetJSON();
    Doc["classrooms"] = (new DataController<TT_Classroom>(OrderManager::Instance().GetClassrooms()))->GetJSON();
    Doc["loop"] = (new DataController<TT_Week>(OrderManager::Instance().GetWeeks()))->GetJSON();
    this->docId->setObject(Doc);

    QFile fileId(QString("timetable.json"));

    if (!fileId.open(QIODevice::WriteOnly)) {
        printf("Data file connot be opened to save.\n");
    } else {
        fileId.write(this->docId->toJson());
    }
}

QJsonDocument *InitData::GetDoc() {
    return this->docId;
}
