#include "ui_teachersadddialog.h"

UI_TeachersAddDialog::UI_TeachersAddDialog(QWidget *parent, TT_Teacher *teacher) :QDialog(parent), CurrentObject(0) {
    setWindowTitle("Добавить преподавателя");
    setFixedWidth(450);

    QVBoxLayout *MainLayout = new QVBoxLayout;
    QFormLayout *FormLayout = new QFormLayout;

    /* Name 1 */
    Name1LineEdit = new QLineEdit;
    Name1LineEdit->setFixedWidth(240);
    Name1LineEdit->setStyleSheet("padding: 3px;");

    UI_NameValidator *pName1Validator = new UI_NameValidator(Name1LineEdit, true);
    Name1LineEdit->setValidator(pName1Validator);

    /* Name 2 */
    Name2LineEdit = new QLineEdit;
    Name2LineEdit->setFixedWidth(240);
    Name2LineEdit->setStyleSheet("padding: 3px;");

    UI_NameValidator *pName2Validator = new UI_NameValidator(Name2LineEdit, true);
    Name2LineEdit->setValidator(pName2Validator);

    /* Name 3 */
    Name3LineEdit = new QLineEdit;
    Name3LineEdit->setFixedWidth(240);
    Name3LineEdit->setStyleSheet("padding: 3px;");

    UI_NameValidator *pName3Validator = new UI_NameValidator(Name3LineEdit, true);
    Name3LineEdit->setValidator(pName3Validator);

    FormLayout->setSpacing(15);
    FormLayout->addRow(tr("Прізвище викладача:"), Name1LineEdit);
    FormLayout->addRow(tr("Ім'я викладача:"), Name2LineEdit);
    FormLayout->addRow(tr("По батькові викладача:"), Name3LineEdit);

    ButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(ButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnButtonClick(QAbstractButton*)));

    if (teacher) SetObject(teacher);

    MainLayout = new QVBoxLayout;
    MainLayout->addLayout(FormLayout);
    MainLayout->addWidget(ButtonBox);
    setLayout(MainLayout);
}

void UI_TeachersAddDialog::SetObject(TT_Teacher *teacher) {
    CurrentObject = teacher;
    setWindowTitle("Редагувати викладача");
    QList<QString> name = teacher->GetName();
    Name1LineEdit->setText(name.at(0));
    Name2LineEdit->setText(name.at(1));
    Name3LineEdit->setText(name.at(2));
}

void UI_TeachersAddDialog::OnButtonClick(QAbstractButton *btn) {
    QDialogButtonBox::StandardButton stdBtn = ButtonBox->standardButton(btn);
    if (stdBtn == QDialogButtonBox::Ok) {
        TT_Teacher *NT = new TT_Teacher;
        QList<QString> name;
        name << Name1LineEdit->text() << Name2LineEdit->text() << Name3LineEdit->text();
        NT->SetName(name);
        if (CurrentObject) {
            NT->SetId(CurrentObject->GetId());
            OrderManager::Instance().Replace(CurrentObject, NT);
        } else {
            OrderManager::Instance().Add(NT);
        }
    }
}
