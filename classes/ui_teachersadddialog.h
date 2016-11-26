#ifndef UI_TEACHERSADDDIALOG_H
#define UI_TEACHERSADDDIALOG_H

#include <QtWidgets>
#include "ordermanager.h"
#include "tt_teacher.h"
#include "ui_namevalidator.h"

class UI_TeachersAddDialog : public QDialog {
    Q_OBJECT
    QDialogButtonBox *ButtonBox;
    QLineEdit *Name1LineEdit, *Name2LineEdit, *Name3LineEdit;
    TT_Teacher *CurrentObject;
public:
    explicit UI_TeachersAddDialog(QWidget* = 0, TT_Teacher* = 0);
    void SetObject(TT_Teacher*);
public slots:
    void OnButtonClick(QAbstractButton*);
};

#endif // UI_TEACHERSADDDIALOG_H
