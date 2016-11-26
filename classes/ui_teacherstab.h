#ifndef UI_TEACHERSTAB_H
#define UI_TEACHERSTAB_H

#include <QtWidgets>

#include "ordermanager.h"
#include "ui_teachersadddialog.h"
#include "initdata.h"

class UI_TeachersTab : public QWidget {
    Q_OBJECT
    QLineEdit *FilterWidget;
    QListWidget *ListWidget;
    QPushButton *AddButton, *EditButton, *RemoveButton;
    QString FilterQuery;
public:
    explicit UI_TeachersTab();
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

#endif // UI_TEACHERSTAB_H
