#ifndef EXPORT_H
#define EXPORT_H

#include <QtWidgets>
#include "mustache.h"
#include "ordermanager.h"
#include "tt_order.h"
#include "tt_week.h"

class Export : public QWidget {
    Q_OBJECT
    QVariantMap data;
    QTime exportTime;
public:
    Export();
    QString ReadTPL();
    QVariantMap GetOrder(TT_Order*);
    QVariantMap GetWeek(TT_Week*);
};

#endif // EXPORT_H
