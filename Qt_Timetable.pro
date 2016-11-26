QT += core
QT -= gui
QT += qml
QT += widgets

CONFIG += c++11
TARGET = Qt_Timetable
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./classes

SOURCES += main.cpp \
    classes/initdata.cpp \
    classes/tt_subject.cpp \
    classes/tt_teacher.cpp \
    classes/tt_classroom.cpp \
    classes/tt_order.cpp \
    classes/tt_item.cpp \
    classes/ordermanager.cpp \
    classes/tt_day.cpp \
    classes/tt_week.cpp \
    classes/ui_mainwindow.cpp \
    classes/ui_managedialog.cpp \
    classes/ui_subjectstab.cpp \
    classes/ui_subjectsadddialog.cpp \
    classes/ui_namevalidator.cpp \
    classes/ui_teacherstab.cpp \
    classes/ui_teachersadddialog.cpp \
    classes/ui_classroomstab.cpp \
    classes/ui_classroomsadddialog.cpp \
    classes/ui_timetableeditdialog.cpp \
    classes/ui_itemdraggable.cpp \
    classes/ui_tableitem.cpp \
    classes/ui_edittable.cpp \
    classes/export.cpp \
    classes/mustache.cpp

HEADERS += \
    classes/initdata.h \
    classes/tt_subject.h \
    classes/datacontroller.h \
    classes/tt_teacher.h \
    classes/tt_classroom.h \
    classes/tt_order.h \
    classes/tt_item.h \
    classes/ordermanager.h \
    classes/tt_day.h \
    classes/tt_week.h \
    classes/ui_mainwindow.h \
    classes/ui_managedialog.h \
    classes/ui_subjectstab.h \
    classes/ui_subjectsadddialog.h \
    classes/ui_namevalidator.h \
    classes/ui_teacherstab.h \
    classes/ui_teachersadddialog.h \
    classes/ui_classroomstab.h \
    classes/ui_classroomsadddialog.h \
    classes/ui_timetableeditdialog.h \
    classes/ui_itemdraggable.h \
    classes/ui_tableitem.h \
    classes/ui_edittable.h \
    classes/export.h \
    classes/mustache.h

DISTFILES +=

RESOURCES += \
    resources.qrc

