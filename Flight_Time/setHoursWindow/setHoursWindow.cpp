#include <QApplication>
#include <QDialog>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"


setHoursWindow::setHoursWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromSetHours()));
}

void setHoursWindow::returnMainMenuFromSetHours()
{
    emit close_me();
    close();
}
