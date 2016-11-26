#include "ui_itemdraggable.h"

UI_ItemDraggable::UI_ItemDraggable(QWidget *parent) : QListWidget(parent) {
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFixedHeight(200);
    setDragEnabled(true);
}

void UI_ItemDraggable::dragMoveEvent(QDragMoveEvent *event) {
    if (event->source() != this) {
        event->accept();
    } else {
        event->ignore();
    }
}

QMimeData *UI_ItemDraggable::mimeData(const QList<QListWidgetItem *> items) const {
    QJsonObject jsonObj = items.at(0)->data(Qt::UserRole).toJsonObject();
    QJsonDocument doc(jsonObj);
    QString plainText(doc.toJson(QJsonDocument::Compact));
    QMimeData *data = new QMimeData;
    data->setText(plainText);
    return data;
}
