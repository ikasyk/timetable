#ifndef UI_SUBJECTSTAB_H
#define UI_SUBJECTSTAB_H

#include <QtWidgets>

#include "ordermanager.h"
#include "ui_subjectsadddialog.h"
#include "initdata.h"

class UI_SubjectsTab : public QWidget {
    Q_OBJECT
    QLineEdit *FilterWidget;
    QListWidget *ListWidget;
    QPushButton *AddButton, *EditButton, *RemoveButton;
    QString FilterQuery;
public:
    explicit UI_SubjectsTab();
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

#endif // UI_SUBJECTSTAB_H
