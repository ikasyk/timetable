#ifndef UI_MANAGEDIALOG_H
#define UI_MANAGEDIALOG_H

#include <QtWidgets>

#include "ui_subjectstab.h"
#include "ui_teacherstab.h"
#include "ui_classroomstab.h"
#include "initdata.h"
#include "datacontroller.h"
#include "ordermanager.h"

class UI_ManageDialog : public QDialog {
    Q_OBJECT
    QTabWidget *TabWidget;
    QDialogButtonBox *ButtonBox;
public:
    explicit UI_ManageDialog(QWidget* = 0);
    void Save();
};

#endif // UI_MANAGEDIALOG_H
