#include "ui_edittable.h"

UI_EditTable::UI_EditTable(TT_Week *w, QWidget *parent) : QTableWidget(parent), week(w) {
    setFrameStyle(QFrame::NoFrame);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    verticalHeader()->setUpdatesEnabled(false);
    setRowCount(3);
    setColumnCount(6);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QTableWidget::item { padding: 0px; border: 0px; }");
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(showContextMenu(QPoint)));


    for (int i = 0; i < horizontalHeader()->count(); ++i) {
        horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for (int j = 0; j < verticalHeader()->count(); ++j) {
            setCellWidget(j, i, new UI_TableItem);
        }
    }
    updateHeight();
}

void UI_EditTable::updateHeight() {
    unsigned int sum = horizontalHeader()->height();
    for (int i = 0; i < rowCount(); ++i) {
        setRowHeight(i, 75);
        sum += 75;
    }
    setMinimumHeight(sum);
    setMaximumHeight(sum);
}

bool UI_EditTable::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action) {
    QString dataText = data->text();
    QJsonDocument doc = QJsonDocument::fromJson(dataText.toUtf8());
    QJsonObject jsonObj = doc.object();
    UI_TableItem *item;
    if (cellWidget(row, column)) {
        item = dynamic_cast<UI_TableItem*>(cellWidget(row, column));
    } else {
        item = new UI_TableItem;
        setCellWidget(row, column, item);
    }
    while (week->GetDays()->size() - 1 < column) {
        week->GetDays()->append(new TT_Day);
    }
    TT_Day *pDay = week->GetDays()->at(column);
    while (pDay->GetOrders()->size() - 1 < row) {
        pDay->GetOrders()->append(new TT_Order);
    }
    TT_Order *pOrder = pDay->GetOrders()->at(row);
    item->setOrder(pOrder);

    if (jsonObj["dt"].toInt() == 1)
        item->setSubject(jsonObj["id"].toInt());
    else if (jsonObj["dt"].toInt() == 2)
        item->setTeacher(jsonObj["id"].toInt());
    else if (jsonObj["dt"].toInt() == 3)
        item->setClassroom(jsonObj["id"].toInt());
//        qDebug() << dataText;
    return true;
}

QStringList UI_EditTable::mimeTypes() const {
    QStringList typesList;
    typesList.append("text/plain");
    return typesList;
}

Qt::DropActions UI_EditTable::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}

void UI_EditTable::showContextMenu(QPoint point) {
    QModelIndexList indexes = selectedIndexes();
    QModelIndex index = indexAt(point);
    if (cellWidget(index.row(), index.column())) {
        QMenu *m = new QMenu(this);
        m->addAction("Очистити предмет", this, SLOT(SlotDeleteSubject()));
        m->addAction("Очистити викладача", this, SLOT(SlotDeleteTeacher()));
        m->addAction("Очистити аудиторію", this, SLOT(SlotDeleteClassroom()));
        m->addAction("Очистити все", this, SLOT(SlotDeleteAll()));
        m->popup(viewport()->mapToGlobal(point));
    }
}

void UI_EditTable::SlotDeleteSubject() {
    QModelIndexList indexes = selectedIndexes();
    QTableWidgetItem *it;
    for (int i = 0; i < indexes.size(); i++) {
        it = item(indexes[i].row(), indexes[i].column());
        if (cellWidget(indexes[i].row(), indexes[i].column())) {
            dynamic_cast<UI_TableItem*>(cellWidget(indexes[i].row(), indexes[i].column()))->setSubject();
        }
    }
}

void UI_EditTable::SlotDeleteTeacher() {
    QModelIndexList indexes = selectedIndexes();
    QTableWidgetItem *it;
    for (int i = 0; i < indexes.size(); i++) {
        it = item(indexes[i].row(), indexes[i].column());
        if (cellWidget(indexes[i].row(), indexes[i].column())) {
            dynamic_cast<UI_TableItem*>(cellWidget(indexes[i].row(), indexes[i].column()))->setTeacher();
        }
    }
}


void UI_EditTable::SlotDeleteClassroom() {
    QModelIndexList indexes = selectedIndexes();
    QTableWidgetItem *it;
    for (int i = 0; i < indexes.size(); i++) {
        it = item(indexes[i].row(), indexes[i].column());
        if (cellWidget(indexes[i].row(), indexes[i].column())) {
            dynamic_cast<UI_TableItem*>(cellWidget(indexes[i].row(), indexes[i].column()))->setClassroom();
        }
    }
}

void UI_EditTable::SlotDeleteAll() {
    QModelIndexList indexes = selectedIndexes();
    QTableWidgetItem *it;
    UI_TableItem *ti;
    for (int i = 0; i < indexes.size(); i++) {
        it = item(indexes[i].row(), indexes[i].column());
        if (cellWidget(indexes[i].row(), indexes[i].column())) {
            ti = dynamic_cast<UI_TableItem*>(cellWidget(indexes[i].row(), indexes[i].column()));
            ti->setSubject();
            ti->setTeacher();
            ti->setClassroom();
        }
    }
}
