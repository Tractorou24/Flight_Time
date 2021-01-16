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
    setHours->setStyleSheet("QPushButton{border-image: url(images/mainWindow/setHours.png)}");

    seeHours = new QPushButton("Voir les heures", this);
    seeHours->setGeometry(280, 160, 160, 160);
    seeHours->setStyleSheet("QPushButton{border-image: url(images/mainWindow/seeHours.jpg)}");

    options = new QPushButton("Options", this);
    options->setGeometry(480, 160, 160, 160);
    options->setStyleSheet("QPushButton{border-image: url(images/mainWindow/seeOptions.png)}");

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

    while (showAddHours)
    {
        setHourWindow->exec();
    }
    delete setHourWindow;
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

    while (showSeeHours)
    {
        seeHourWindow->exec();
    }
    delete seeHourWindow;
}

void mainWindow::seeOptions()
{
    seeOptionWindow = new seeOptionsWindow(this);
    QObject::connect(seeOptionWindow, SIGNAL(close_me()), this, SLOT(closeChild()));
    showSeeOptions = true;

    while (showSeeOptions)
    {
        seeOptionWindow->exec();
    }
    delete seeOptionWindow;
}

std::string mainWindow::QStrToStr(QString QStr)
{
    return QStr.toLocal8Bit().constData();
}

QString mainWindow::StrToQStr(std::string str)
{
    return QString::fromStdString(str);
}