#include "ui_tableitem.h"

UI_TableItem::UI_TableItem(QWidget *parent) : QWidget(parent), subject_id(0), teacher_id(0), classroom_id(0) {
    order = new TT_Order;
    QFont subjectFont("Helvetica", 12, QFont::Normal, false);
    QFont teacherFont("Helvetica", 11, QFont::Normal, false);

    layout = new QVBoxLayout;

    subjectLabel = new QLabel;
    subjectLabel->setFont(subjectFont);
    subjectLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    subjectLabel->setWordWrap(true);

    subjectLayout = new QHBoxLayout;
    subjectLayout->addWidget(subjectLabel);
    layout->addLayout(subjectLayout);

    teacherLabel = new QLabel;
    teacherLabel->setFont(teacherFont);
    teacherLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    teacherLabel->setWordWrap(true);
    teacherLabel->setFixedHeight(14);
    teacherLayout = new QHBoxLayout;
    teacherLayout->addWidget(teacherLabel);
    layout->addLayout(teacherLayout);

    classroomLabel = new QLabel;
    classroomLabel->setFont(teacherFont);
    classroomLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    classroomLabel->setWordWrap(true);
    classroomLabel->setFixedHeight(14);
    classroomLayout = new QHBoxLayout;
    classroomLayout->addWidget(classroomLabel);
    layout->setMargin(3);
    layout->addLayout(classroomLayout);

    setLayout(layout);
}

void UI_TableItem::setSubject(int id) {
    if (id < 0) return;
    if (id == 0) {
        this->subject_id = 0;
        subjectLabel->setText("");
        order->SetIds(0);
        return;
    }

    this->subject_id = id;

    TT_Subject *subject = OrderManager::Instance().GetSubjects()->at(id - 1);
    QFontMetrics metrix(subjectLabel->font());
    QString labelText = metrix.elidedText(subject->GetName(), Qt::ElideRight, subjectLabel->width());
    labelText = QString("<b>%1</b>").arg(labelText);
    if (subject->GetType() == 1) {
        labelText += " <i>лекція</i>";
    } else if (subject->GetType() == 2) {
        labelText += " <i>практика</i>";
    } else if (subject->GetType() == 3) {
        labelText += " <i>лабораторна</i>";
    }
    subjectLabel->setText(labelText);
    order->SetIds(id);
}

void UI_TableItem::setTeacher(int id) {
    if (id < 0) return;
    if (id == 0) {
        this->teacher_id = 0;
        teacherLabel->setText("");
        order->SetIds(-1, 0);
        return;
    }

    this->teacher_id = id;
    QString labelText = OrderManager::Instance().GetTeachers()->at(id - 1)->GetShortName();
    teacherLabel->setText(labelText);
    order->SetIds(-1, id);
}

void UI_TableItem::setClassroom(int id) {
    if (id < 0) return;
    if (id == 0) {
        this->classroom_id = 0;
        classroomLabel->setText("");
        order->SetIds(-1, -1, 0);
        return;
    }

    this->classroom_id = id;
    QString labelText = OrderManager::Instance().GetClassrooms()->at(id - 1)->GetFullRoom();
    classroomLabel->setText(labelText);
    order->SetIds(-1, -1, id);
}

void UI_TableItem::setOrder(TT_Order *ord) {
    this->order = ord;
}

void UI_TableItem::SlotDeleteSubject() {
    setSubject();
}

void UI_TableItem::SlotDeleteTeacher() {
    setTeacher();
}

void UI_TableItem::SlotDeleteClassroom() {
    setClassroom();
}

void UI_TableItem::SlotDeleteAll() {
    setSubject();
    setTeacher();
    setClassroom();
}
