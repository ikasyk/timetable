#ifndef UI_EDITTABLE_H
#define UI_EDITTABLE_H

#include <QtWidgets>
#include "ui_tableitem.h"

class UI_EditTable : public QTableWidget {
    Q_OBJECT
    TT_Week *week;
public:
    UI_EditTable(TT_Week*, QWidget* = 0);
    void updateHeight();
protected:
    virtual bool dropMimeData(int, int, const QMimeData *, Qt::DropAction action);
    virtual QStringList mimeTypes() const;
    virtual Qt::DropActions supportedDropActions() const;
public slots:
    void showContextMenu(QPoint);
    void SlotDeleteSubject();
    void SlotDeleteTeacher();
    void SlotDeleteClassroom();
    void SlotDeleteAll();
};

#endif // UI_EDITTABLE_H
