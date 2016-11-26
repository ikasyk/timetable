#include "ui_classroomsadddialog.h"

UI_ClassroomsAddDialog::UI_ClassroomsAddDialog(QWidget *parent, TT_Classroom *classroom) :QDialog(parent), CurrentObject(0) {
    setWindowTitle("Додати аудиторію");
    setFixedWidth(450);

    QVBoxLayout *MainLayout = new QVBoxLayout;
    QFormLayout *FormLayout = new QFormLayout;

    CorpusLineEdit = new QLineEdit;
    CorpusLineEdit->setFixedWidth(200);
    CorpusLineEdit->setStyleSheet("padding: 3px;");

    QIntValidator *CorpusValidator = new QIntValidator(1, 50, CorpusLineEdit);
    CorpusLineEdit->setValidator(CorpusValidator);

    RoomLineEdit = new QLineEdit;
    RoomLineEdit->setFixedWidth(200);
    RoomLineEdit->setStyleSheet("padding: 3px;");

    UI_NameValidator *RoomValidator = new UI_NameValidator(RoomLineEdit, false);
    RoomLineEdit->setValidator(RoomValidator);

    FormLayout->setSpacing(15);
    FormLayout->addRow(tr("Корпус №:"), CorpusLineEdit);
    FormLayout->addRow(tr("Аудитория №:"), RoomLineEdit);

    ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(ButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnButtonClick(QAbstractButton*)));

    if (classroom) SetObject(classroom);

    MainLayout = new QVBoxLayout;
    MainLayout->addLayout(FormLayout);
    MainLayout->addWidget(ButtonBox);
    setLayout(MainLayout);
}

void UI_ClassroomsAddDialog::SetObject(TT_Classroom *classroom) {
    CurrentObject = classroom;
    setWindowTitle("Редагувати аудиторію");
    CorpusLineEdit->setText(QString::number(classroom->GetCorpus()));
    RoomLineEdit->setText(classroom->GetRoom());
}

void UI_ClassroomsAddDialog::OnButtonClick(QAbstractButton *btn) {
    QDialogButtonBox::StandardButton stdBtn = ButtonBox->standardButton(btn);
    if (stdBtn == QDialogButtonBox::Ok) {
        TT_Classroom *NC = new TT_Classroom;
        NC->SetCorpus((unsigned short)CorpusLineEdit->text().toInt());
        NC->SetRoom(RoomLineEdit->text());
        if (CurrentObject) {
            NC->SetId(CurrentObject->GetId());
            OrderManager::Instance().Replace(CurrentObject, NC);
        } else {
            OrderManager::Instance().Add(NC);
        }
    }
}
