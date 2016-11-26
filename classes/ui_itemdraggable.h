#ifndef UI_ITEMDRAGGABLE_H
#define UI_ITEMDRAGGABLE_H

#include <QtWidgets>
#include <QJsonDocument>
#include "ui_tableitem.h"

class UI_ItemDraggable : public QListWidget {
    Q_OBJECT
protected:
    void dragMoveEvent(QDragMoveEvent*);
    virtual QMimeData *mimeData(const QList<QListWidgetItem *>) const;
public:
    UI_ItemDraggable(QWidget* = 0);
};


#endif // UI_ITEMDRAGGABLE_H
