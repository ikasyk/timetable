#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>

#include "ui_managedialog.h"
#include "ui_timetableeditdialog.h"
#include "ui_tableitem.h"
#include "export.h"

class UI_MainWindow : public QMainWindow {
    Q_OBJECT
    QVBoxLayout *MainLayout, *TT_Layout;
    QWidget *MainWidget, *TT_Wrap;
public:
    UI_MainWindow();
    void BuildTable();
    void RemoveTable();
    void RebuildTable();
    void AddWeek(TT_Week*);
public slots:
    void ControlButtonClick();
    void TimetableEditClick();
    void ExportClick();
};

#endif // UI_MAINWINDOW_H
