#include "ui_managedialog.h"

UI_ManageDialog::UI_ManageDialog(QWidget *parent) :QDialog(parent) {
    setWindowTitle(tr("Керування даними"));
    setFixedSize(600, 400);

    TabWidget = new QTabWidget;
    TabWidget->addTab(new UI_SubjectsTab(), tr("Предмети"));
    TabWidget->addTab(new UI_TeachersTab(), tr("Викладачі"));
    TabWidget->addTab(new UI_ClassroomsTab(), tr("Аудиторії"));

    ButtonBox = new QDialogButtonBox();
    connect(ButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *MainLayout = new QVBoxLayout(this);
    MainLayout->addWidget(TabWidget);
    setLayout(MainLayout);
    //setCentralWidget(MainWidget);
}
