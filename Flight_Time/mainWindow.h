#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "setHoursWindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void addHours();
    void showHours();
    void seeOptions();

private:
    setHoursWindow* setHourWindow;

    QPushButton* setHours;
    QPushButton* seeHours;
    QPushButton* options;
    QPushButton* mainQuit;
};

#endif
