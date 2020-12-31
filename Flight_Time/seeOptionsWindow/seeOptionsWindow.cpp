#include <QApplication>
#include <QDialog>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"

seeOptionsWindow::seeOptionsWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(720, 480);

    returnMain = new QPushButton("Quitter", this);
    returnMain->setGeometry(620, 430, 100, 50);

    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromOptions()));
}

void seeOptionsWindow::returnMainMenuFromOptions()
{
    emit close_me();
    close();
}
