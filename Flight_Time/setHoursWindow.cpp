#include <QApplication>
#include <QDialog>
#include "setHoursWindow.h"

setHoursWindow::setHoursWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(720, 480);

    mainQuit = new QPushButton("Quitter", this);
    mainQuit->setGeometry(620, 430, 100, 50);

    QObject::connect(mainQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}
