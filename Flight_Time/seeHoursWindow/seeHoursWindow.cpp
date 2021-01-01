#include <QApplication>
#include <QDialog>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"

seeHoursWindow::seeHoursWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromSeeHours()));
}

void seeHoursWindow::returnMainMenuFromSeeHours()
{
    emit close_me();
    close();
}
