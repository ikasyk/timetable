#ifndef UI_SUBJECTSADDDIALOG_H
#define UI_SUBJECTSADDDIALOG_H

#include <QtWidgets>
#include "ordermanager.h"
#include "tt_subject.h"
#include "ui_namevalidator.h"

class UI_SubjectsAddDialog : public QDialog {
    Q_OBJECT
    QDialogButtonBox *ButtonBox;
    QLineEdit *NameLineEdit;
    QComboBox *TypeComboBox;
    TT_Subject *CurrentObject;
public:
    explicit UI_SubjectsAddDialog(QWidget* = 0, TT_Subject* = 0);
    void SetObject(TT_Subject*);
public slots:
    void OnButtonClick(QAbstractButton*);
};

#endif // UI_SUBJECTSADDDIALOG_H
