#ifndef UI_CLASSROOMSTAB_H
#define UI_CLASSROOMSTAB_H

#include <QtWidgets>

#include "ordermanager.h"
#include "ui_classroomsadddialog.h"
#include "initdata.h"

class UI_ClassroomsTab : public QWidget {
    Q_OBJECT
    QLineEdit *FilterWidget;
    QListWidget *ListWidget;
    QPushButton *AddButton, *EditButton, *RemoveButton;
    QString FilterQuery;
public:
    explicit UI_ClassroomsTab();
    void MakeList();
    void CheckButtons();
public slots:
    void AddButtonClicked();
    void EditButtonClicked();
    void RemoveButtonClicked();
    void CheckButtonsSlot();
    void MakeListByFilter(const QString &);
    void ListItemClicked(QListWidgetItem *);
};

#endif // UI_CLASSROOMSTAB_H
