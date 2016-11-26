#include "ui_subjectsadddialog.h"

UI_SubjectsAddDialog::UI_SubjectsAddDialog(QWidget *parent, TT_Subject *subject) :QDialog(parent), CurrentObject(0) {
    setWindowTitle("Добавить предмет");
    setFixedWidth(450);

    QVBoxLayout *MainLayout = new QVBoxLayout;
    QFormLayout *FormLayout = new QFormLayout;

    NameLineEdit = new QLineEdit;
    NameLineEdit->setFixedWidth(240);
    NameLineEdit->setStyleSheet("padding: 3px;");

    UI_NameValidator *pNameValidator = new UI_NameValidator(NameLineEdit);
    NameLineEdit->setValidator(pNameValidator);

    TypeComboBox = new QComboBox;
    TypeComboBox->addItem(tr("Лекція"), 1);
    TypeComboBox->addItem(tr("Практика"), 2);
    TypeComboBox->addItem(tr("Лабораторна"), 3);

    FormLayout->setSpacing(15);
    FormLayout->addRow(tr("Назва предмету:"), NameLineEdit);
    FormLayout->addRow(tr("Тип предмету:"), TypeComboBox);

    ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(ButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnButtonClick(QAbstractButton*)));

    if (subject) SetObject(subject);

    MainLayout = new QVBoxLayout;
    MainLayout->addLayout(FormLayout);
    MainLayout->addWidget(ButtonBox);
    setLayout(MainLayout);
}

void UI_SubjectsAddDialog::SetObject(TT_Subject *subject) {
    CurrentObject = subject;
    setWindowTitle("Редагувати предмет");
    NameLineEdit->setText(subject->GetName());
    TypeComboBox->setCurrentIndex(subject->GetType() - 1);
}

void UI_SubjectsAddDialog::OnButtonClick(QAbstractButton *btn) {
    QDialogButtonBox::StandardButton stdBtn = ButtonBox->standardButton(btn);
    if (stdBtn == QDialogButtonBox::Ok) {
        TT_Subject *NS = new TT_Subject;
        NS->SetName(NameLineEdit->text());
        NS->SetType(TypeComboBox->itemData(TypeComboBox->currentIndex()).toInt());
        if (CurrentObject) {
            NS->SetId(CurrentObject->GetId());
            OrderManager::Instance().Replace(CurrentObject, NS);
        } else {
            OrderManager::Instance().Add(NS);
        }
    }
}
