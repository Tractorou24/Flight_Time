#include <QApplication>
#include <QDialog>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"


setHoursWindow::setHoursWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(720, 480);

    returnMain = new QPushButton("Quitter", this);
    returnMain->setGeometry(620, 430, 100, 50);

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromSetHours()));
}

void setHoursWindow::returnMainMenuFromSetHours()
{
    emit close_me();
    close();
}
