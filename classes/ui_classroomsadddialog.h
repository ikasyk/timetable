#ifndef UI_CLASSROOMSADDDIALOG_H
#define UI_CLASSROOMSADDDIALOG_H

#include <QtWidgets>
#include "ordermanager.h"
#include "tt_classroom.h"
#include "ui_namevalidator.h"

class UI_ClassroomsAddDialog : public QDialog {
    Q_OBJECT
    QDialogButtonBox *ButtonBox;
    QLineEdit *CorpusLineEdit, *RoomLineEdit;
    TT_Classroom *CurrentObject;
public:
    explicit UI_ClassroomsAddDialog(QWidget* = 0, TT_Classroom* = 0);
    void SetObject(TT_Classroom*);
public slots:
    void OnButtonClick(QAbstractButton*);
};

#endif // UI_CLASSROOMSADDDIALOG_H
