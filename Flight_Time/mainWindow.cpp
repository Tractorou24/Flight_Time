#include "mainWindow.h"
#include <QApplication>
#include <QScreen>
#include <QObject>
#include "setHoursWindow.h"

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
    hide();
    setHourWindow = new setHoursWindow(this);
    setHourWindow->show();
}

void mainWindow::showHours()
{

}

void mainWindow::seeOptions()
{

}
