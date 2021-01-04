#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>
#include "../mainWindow/mainWindow.h"
#include "../setHoursWindow/setHoursWindow.h"
#include "../general/programSettings.h"
#include "database.h"

seeOptionsWindow::seeOptionsWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    label = new QLabel;
    pixmap_img = new QPixmap("images/optionsWindow/background.png");
    label->setPixmap(*pixmap_img);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(label, 0, 0);

    // Show and set database menu
    std::vector<std::string> availableDatabases = getAllAvailableDatabases();
    selectedDBBox = new QComboBox(this);
    selectedDBBox->setGeometry(50, 250, 200, 30);
    for (int i = 0; i < availableDatabases.size(); i++)
    {
        selectedDBBox->addItem(availableDatabases[i].c_str());
    }
    selectedDBBox->setCurrentText(getSelectedDatabase().c_str());
    selectedDBBox->show();

    //Set buttons
    addDatabase = new QPushButton("add database", this);
    addDatabase->setGeometry(50, 40, 100, 50);

    removeDatabase = new QPushButton("remove database", this);
    removeDatabase->setGeometry(50, 140, 100, 50);

    addPlayerinSelectedDatabase = new QPushButton("add player to selected db", this);
    addPlayerinSelectedDatabase->setGeometry(500, 250, 200, 50);

    removePlayerFromSelectedDatabase = new QPushButton("remove player from selected db", this);
    removePlayerFromSelectedDatabase->setGeometry(500, 500, 200, 50);

    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    QObject::connect(addDatabase, SIGNAL(clicked()), this, SLOT(addDB()));
    QObject::connect(removeDatabase, SIGNAL(clicked()), this, SLOT(rmDB()));
    QObject::connect(addPlayerinSelectedDatabase, SIGNAL(clicked()), this, SLOT(addPlayerInDB()));
    QObject::connect(removePlayerFromSelectedDatabase, SIGNAL(clicked()), this, SLOT(rmPlayerFromDB()));
    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromOptions()));
    QObject::connect(selectedDBBox, SIGNAL(currentTextChanged(QString)), this, SLOT(setDatabase(QString)));
}

void seeOptionsWindow::addDB()
{
    AddDbRequestBox = new QDialog(this);
    AddDbRequestBox->setFixedSize(300, 150);
    AddDbRequestBox->setWindowTitle("Add a database :");

    AddDbDbName = new QLineEdit(AddDbRequestBox);
    AddDbDbName->setGeometry(25, 40, 250, 25);
    AddDbDbName->show();

    AddDbOk = new QPushButton("Ok", AddDbRequestBox);
    AddDbOk->setGeometry(65, 90, 50, 25);

    AddDbCancel = new QPushButton("Cancel", AddDbRequestBox);
    AddDbCancel->setGeometry(200, 90, 50, 25);

    QObject::connect(AddDbOk, SIGNAL(clicked()), this, SLOT(createDB()));
    QObject::connect(AddDbCancel, SIGNAL(clicked()), this, SLOT(deleteCreateDB()));

    AddDbRequestBox->exec();
}

void seeOptionsWindow::createDB() {
    if (db.dbExist(AddDbDbName->text().toStdString()))
    {
        QMessageBox ErrorBox;
        ErrorBox.setText("Database already exist.");
        ErrorBox.exec();
        deleteCreateDB();
        addDB();
    }
    else {
        db.addDatabase(AddDbDbName->text().toStdString());
        deleteCreateDB();
    }
}

void seeOptionsWindow::deleteCreateDB()
{
    AddDbRequestBox->close();
    delete AddDbRequestBox, AddDbDbName, AddDbOk, AddDbCancel;
}


void seeOptionsWindow::rmDB()
{
    RmDbRequestBox = new QDialog(this);
    RmDbRequestBox->setFixedSize(300, 150);
    RmDbRequestBox->setWindowTitle("Remove a database :");

    std::vector<std::string> availableDatabases = getAllAvailableDatabases();
    rmDbBox = new QComboBox(RmDbRequestBox);
    rmDbBox->setGeometry(50, 50, 200, 25);
    for (int i = 0; i < availableDatabases.size(); i++)
    {
        rmDbBox->addItem(availableDatabases[i].c_str());
    }
    rmDbBox->show();

    RmDbOk = new QPushButton("Ok", RmDbRequestBox);
    RmDbOk->setGeometry(65, 90, 50, 25);

    RmDbCancel = new QPushButton("Cancel", RmDbRequestBox);
    RmDbCancel->setGeometry(200, 90, 50, 25);

    QObject::connect(RmDbOk, SIGNAL(clicked()), this, SLOT(deleteDB()));
    QObject::connect(RmDbCancel, SIGNAL(clicked()), this, SLOT(deleteDeleteDB()));

    RmDbRequestBox->exec();
}

void seeOptionsWindow::deleteDB() {
    db.deleteDatabase(rmDbBox->currentText().toStdString());
    deleteDeleteDB();
}

void seeOptionsWindow::deleteDeleteDB()
{
    RmDbRequestBox->close();
    delete RmDbRequestBox, rmDbBox, RmDbOk, RmDbCancel;
}


void seeOptionsWindow::addPlayerInDB()
{

}

void seeOptionsWindow::rmPlayerFromDB()
{

}

void seeOptionsWindow::setDatabase(QString QStr)
{
    setSelectedDatabase(QStr.toStdString());
}

void seeOptionsWindow::returnMainMenuFromOptions()
{
    delete gridLayout;
    delete pixmap_img;
    delete label;

    delete selectedDBBox;

    delete addDatabase;
    delete removeDatabase;
    delete addPlayerinSelectedDatabase;
    delete removePlayerFromSelectedDatabase;
    delete returnMain;

    emit close_me();
    close();
}
