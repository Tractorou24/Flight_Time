#include <QApplication>
#include <QDialog>
#include <iostream>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"
#include "database.h"

seeOptionsWindow::seeOptionsWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    database db;
    std::vector<std::string> infos;
    db.addDatabase("VF84");
    infos.push_back("Modex : 206");
    infos.push_back("POKER 2020");
    infos.push_back("ENTREE 12/10/2020");
    db.addPlayerToDatabase("VF84", "206 Tracto", infos);
    db.addAnHourInDatabase("VF84", "206 Tracto", "allTime", 2.0);
    db.addADateInDatabase("VF84", "206 Tracto", "caseIDeparture", "2/10/2019");

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromOptions()));
}

void seeOptionsWindow::returnMainMenuFromOptions()
{
    emit close_me();
    close();
}
