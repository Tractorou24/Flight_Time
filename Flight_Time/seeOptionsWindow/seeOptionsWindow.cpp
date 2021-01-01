#include <QApplication>
#include <QDialog>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"

seeOptionsWindow::seeOptionsWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromOptions()));
}

void seeOptionsWindow::returnMainMenuFromOptions()
{
    emit close_me();
    close();
}
