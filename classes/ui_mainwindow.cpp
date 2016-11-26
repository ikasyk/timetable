#include "ui_mainwindow.h"

UI_MainWindow::UI_MainWindow() {
    setWindowTitle(QString("iRozklad"));
    resize(QSize(750, 500));
    setMinimumSize(480, 200);

    MainWidget = new QWidget(this);
    QWidget *TopWidget = new QWidget(this);

    TopWidget->setObjectName("top_logo");
    TopWidget->setStyleSheet("#top_logo { background: center center url(://images/irozklad.png) no-repeat; }");
    TopWidget->setMinimumHeight(100);

    QGridLayout *TopLayout = new QGridLayout;
    TopLayout->setAlignment(Qt::AlignRight);

    QPushButton *ControlButton = new QPushButton();
    ControlButton->setObjectName("control_button");
    ControlButton->setFlat(true);
    ControlButton->setIconSize(QSize(72, 18));
    ControlButton->setFixedSize(52, 28);
    ControlButton->setIcon(QPixmap("://images/settings.png"));

    QMenu *ControlMenu = new QMenu(ControlButton);
    QAction *Separator = new QAction(ControlMenu);
    Separator->setSeparator(true);
    ControlMenu->addAction("Керування даними", this, SLOT(ControlButtonClick()));
    ControlMenu->addAction("Редагувати розклад", this, SLOT(TimetableEditClick()));
    ControlMenu->addAction(Separator);
    ControlMenu->addAction("Експортувати в .html", this, SLOT(ExportClick()));
    ControlButton->setMenu(ControlMenu);

    TopLayout->addWidget(ControlButton);
    TopWidget->setLayout(TopLayout);

    QScrollArea *TT_Scroll = new QScrollArea;
    TT_Scroll->setObjectName("tt_scroll_area");
    TT_Scroll->setWidgetResizable(true);
    TT_Scroll->setStyleSheet("#tt_scroll_area { border: 0; border-top: 1px solid #c3c3c3; }");


    TT_Wrap = new QWidget;
    TT_Wrap->setObjectName("tt_wrap");
    TT_Wrap->setStyleSheet("#tt_wrap { background: #FFF; }");
    TT_Wrap->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //TT_Wrap->setLayout(TT_Layout);
    TT_Scroll->setWidget(TT_Wrap);

    MainLayout = new QVBoxLayout;
    MainLayout->setMargin(0);
    MainLayout->setAlignment(Qt::AlignTop);
    MainLayout->addWidget(TopWidget);
    MainLayout->addWidget(TT_Scroll);
    MainWidget->setLayout(MainLayout);
    setCentralWidget(MainWidget);

    BuildTable();

    MainWidget->show();
}

void UI_MainWindow::ControlButtonClick() {
    UI_ManageDialog *ManDialog = new UI_ManageDialog(this);
    ManDialog->exec();
    delete ManDialog;
}

void UI_MainWindow::BuildTable() {
    TT_Layout = new QVBoxLayout;
    QList<TT_Week*>* weeks = OrderManager::Instance().GetWeeks();
    for (int i = 0; i < weeks->size(); i++) {
        AddWeek(weeks->at(i));
    }
    TT_Wrap->setLayout(TT_Layout);
}

void UI_MainWindow::RemoveTable() {
    delete TT_Layout;
}

void UI_MainWindow::RebuildTable() {
    RemoveTable();
    BuildTable();
}

void UI_MainWindow::TimetableEditClick() {
    UI_TimetableEditDialog *EditDialog = new UI_TimetableEditDialog(this);
    EditDialog->exec();
    delete EditDialog;
}

void UI_MainWindow::ExportClick() {
    new Export();
}

void UI_MainWindow::AddWeek(TT_Week *week) {
    QVBoxLayout *weekLayout = new QVBoxLayout;
    QLabel *label = new QLabel( QString("<h3 align=\"center\"><i>Тиждень %1</i></h3>").arg(week->GetId()) );
    label->setStyleSheet("color: #2b6084;");
    weekLayout->addWidget(label);
    QStringList weekDays;
    weekDays << "Понеділок" << "Вівторок" << "Середа" << "Четвер" << "П'ятниця" << "Субота";
    QTableWidget *table = new QTableWidget(this);
    table->setFrameStyle(QFrame::NoFrame);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setRowCount(2);
    table->setColumnCount(6);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setStyleSheet("QTableWidget::item { padding: 0px; border: 0px; }");
    table->setHorizontalHeaderLabels(weekDays);

    weekLayout->addWidget(table);

    for (int i = 0; i < table->horizontalHeader()->count(); ++i)
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    QList<TT_Day*>* days = week->GetDays();
    for (int i = 0; i < days->size(); i++) {
        QList<TT_Order*>* orders = days->at(i)->GetOrders();
        for (int j = 0; j < orders->size(); j++) {
            TT_Order *order = orders->at(j);
            if ((order->GetClassroomId() || order->GetTeacherId() || order->GetSubjectId()) && table->rowCount()-1 < j) {
                while (table->rowCount() <= j)
                    table->insertRow(table->rowCount());
            }
            UI_TableItem *ti = new UI_TableItem;
            ti->setSubject(order->GetSubjectId());
            ti->setTeacher(order->GetTeacherId());
            ti->setClassroom(order->GetClassroomId());
            ti->setOrder(order);
            table->setCellWidget(j, i, ti);
        }
    }

    // Update height
    unsigned int sum = table->horizontalHeader()->height();
    for (int i = 0; i < table->rowCount(); ++i) {
        table->setRowHeight(i, 75);
        sum += 75;
    }
    table->setMinimumHeight(sum);
    table->setMaximumHeight(sum);

    TT_Layout->addLayout(weekLayout);
}
