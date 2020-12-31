#include "mainWindow/mainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    w.setWindowIcon(QIcon("icon.ico"));
    w.setWindowTitle("Filght Time Calculator");
    w.show();
    return a.exec();
}
