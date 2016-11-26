#include "export.h"
#include <QJsonDocument>

Export::Export() {
    QDateTime curTime = QDateTime::currentDateTime();
    data["export_date"] = QVariant(curTime.toString("d.MM.yyyy о h:mm:ss"));

    QString BaseTPL = ReadTPL();

    QVariantList weeks;
    QList<TT_Week*>* weeksData = OrderManager::Instance().GetWeeks();
    for (int i = 0; i < weeksData->size(); i++) {
        QVariantMap m;
        m = GetWeek(weeksData->at(i));
        weeks.append(QVariant(m));
    }
    data["week_table"] = QVariant(weeks);

    QString dir = QFileDialog::getExistingDirectory(this, tr("Виберіть теку для експорту", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks	));
    QString filePath = dir + QString("/Розклад занять " + curTime.toString("d.MM.yyyy h:mm:ss") + ".html");
    QFile exportFile(filePath);

    if (!exportFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    Mustache::Renderer renderer;
    Mustache::QtVariantContext *context = new Mustache::QtVariantContext(data);
    QTextStream output(&exportFile);
    output << renderer.render(BaseTPL, context);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

QString Export::ReadTPL() {
    QFile file("://temp/index.tpl");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream textStream(&file);
        return textStream.readAll();
    }
    return QString();
}

QVariantMap Export::GetOrder(TT_Order *order) {
    QVariantMap orderData;

    if (order->GetSubjectId()) {
        TT_Subject *subject = order->GetSubject();
        QString typeName;
        if (subject->GetType() == 1) {
            typeName = "лекція";
        } else if (subject->GetType() == 2) {
            typeName = "практика";
        } else if (subject->GetType() == 3) {
            typeName = "лабораторна";
        }
        orderData["subject"] = subject->GetName();
        orderData["type"] = typeName;
    } else {
        orderData["subject"] = " ";
        orderData["type"] = "";
    }

    if (order->GetTeacherId()) {
        TT_Teacher *teacher = order->GetTeacher();
        orderData["teacher"] = teacher->GetShortName();
    } else {
        orderData["teacher"] = " ";
    }

    if (order->GetClassroomId()) {
        TT_Classroom *classroom = order->GetClassroom();
        orderData["classroom"] = classroom->GetFullRoom();
    } else {
        orderData["classroom"] = " ";
    }

    return orderData;
}

QVariantMap Export::GetWeek(TT_Week *week) {
    QList<TT_Day*>* days = week->GetDays();
    int n = 0;
    for (int i = 0; i < days->size(); i++)
        if (n < days->at(i)->GetOrders()->size())
            n = days->at(i)->GetOrders()->size();
    QVariantList weekData;
    for (int i = 0; i < n; i++) {
        QVariantMap tr_wrap;
        QVariantList tr;
        for (int j = 0; j < 6; j++) {
            QVariantMap td_wrap;
            QVariantMap td;
            QVariant content;
            if (days->size() > j) {
                TT_Day *day = days->at(j);
                if (day->GetOrders()->size() > i) {
                    TT_Order *order = day->GetOrders()->at(i);
                    if (order->GetSubjectId() || order->GetTeacherId() || order->GetClassroomId()) {
                        content.setValue(GetOrder(order));
                    } else {
                        content.setValue(false);
                    }
                } else {
                    content.setValue(false);
                }
            } else {
                content.setValue(false);
            }
            td["order_content"] = content;
            tr.append(td);
        }
        tr_wrap["row_order"] = tr;
        weekData.append(tr_wrap);
    }
    QVariantMap week_wrap;
    week_wrap["week_row"] = weekData;
    week_wrap["week_id"] = QVariant((int)week->GetId());
    return week_wrap;
}
