#include <QApplication>
#include <QScreen>
#include <QObject>
#include "mainWindow.h"
#include "../seeHoursWindow/seeHoursWindow.h"
#include "../setHoursWindow/setHoursWindow.h"
#include "../seeOptionsWindow/seeOptionsWindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(720, 480);

    setHours = new QPushButton("Ajouter des heures", this);
    setHours->setGeometry(80, 160, 160, 160);

    seeHours = new QPushButton("Voir les heures", this);
    seeHours->setGeometry(280, 160, 160, 160);

    options = new QPushButton("Options", this);
    options->setGeometry(480, 160, 160, 160);

    mainQuit = new QPushButton("Quitter", this);
    mainQuit->setGeometry(620, 430, 100, 50);

    QObject::connect(setHours, SIGNAL(clicked()), this, SLOT(addHours()));
    QObject::connect(seeHours, SIGNAL(clicked()), this, SLOT(showHours()));
    QObject::connect(options, SIGNAL(clicked()), this, SLOT(seeOptions()));
    QObject::connect(mainQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void mainWindow::addHours()
{
    setHourWindow = new setHoursWindow(this);
    QObject::connect(setHourWindow, SIGNAL(close_me()), this, SLOT(closeChild()));
    showAddHours = true;
    this->hide();

    while (showAddHours)
    {
        setHourWindow->exec();
    }
    this->show();
}

void mainWindow::closeChild()
{
    showAddHours = false;
    showSeeHours = false;
    showSeeOptions = false;
}

void mainWindow::showHours()
{
    seeHourWindow = new seeHoursWindow(this);
    QObject::connect(seeHourWindow, SIGNAL(close_me()), this, SLOT(closeChild()));
    showSeeHours = true;
    this->hide();

    while (showSeeHours)
    {
        seeHourWindow->exec();
    }
    this->show();
}

void mainWindow::seeOptions()
{
    seeOptionWindow = new seeOptionsWindow(this);
    QObject::connect(seeOptionWindow, SIGNAL(close_me()), this, SLOT(closeChild()));
    showSeeOptions = true;
    this->hide();

    while (showSeeOptions)
    {
        seeOptionWindow->exec();
    }
    this->show();
}
