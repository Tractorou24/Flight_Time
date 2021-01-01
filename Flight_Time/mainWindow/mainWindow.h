#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "../seeHoursWindow/seeHoursWindow.h"
#include "../setHoursWindow/setHoursWindow.h"
#include "../seeOptionsWindow/seeOptionsWindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);
    std::string QStrToStr(QString QStr);
    QString StrToQStr(std::string str);

private slots:
    void addHours();
    void closeChild();
    void showHours();
    void seeOptions();

private:
    setHoursWindow* setHourWindow;
    seeHoursWindow* seeHourWindow;
    seeOptionsWindow* seeOptionWindow;

    QPushButton* setHours, *seeHours, *options, *mainQuit;
    bool showAddHours, showSeeHours, showSeeOptions;
};

#endif
