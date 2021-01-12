#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <iostream>
#include <vector>
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
    addPlayerRequestBox = new QDialog(this);
    addPlayerRequestBox->setFixedSize(500, 300);
    addPlayerRequestBox->setWindowTitle("Add a player to database :");

    std::vector<std::string> availableDatabases = getAllAvailableDatabases();
    addPlayerInDbBox = new QComboBox(addPlayerRequestBox);
    addPlayerInDbBox->setGeometry(40, 180, 200, 25);
    for (int i = 0; i < availableDatabases.size(); i++)
    {
        addPlayerInDbBox->addItem(availableDatabases[i].c_str());
    }
    addPlayerInDbBox->setCurrentText(getSelectedDatabase().c_str());
    addPlayerInDbBox->show();

    addPlayerInfosTextBox = new QTextEdit(addPlayerRequestBox);
    addPlayerInfosTextBox->setGeometry(280, 60, 200, 160);
    addPlayerInfosTextBox->show();

    addPlayerPlayerName = new QLineEdit(addPlayerRequestBox);
    addPlayerPlayerName->setGeometry(65, 90, 130, 25);
    addPlayerPlayerName->show();

    addPlayerInDbOk = new QPushButton("Ok", addPlayerRequestBox);
    addPlayerInDbOk->setGeometry(100, 240, 50, 25);

    addPlayerInDbCancel = new QPushButton("Cancel", addPlayerRequestBox);
    addPlayerInDbCancel->setGeometry(350, 240, 50, 25);

    QObject::connect(addPlayerInDbOk, SIGNAL(clicked()), this, SLOT(addPlayer()));
    QObject::connect(addPlayerInDbCancel, SIGNAL(clicked()), this, SLOT(deleteAddPlayer()));

    addPlayerRequestBox->exec();
}

void seeOptionsWindow::addPlayer() {
    addPlayerPlayerInfos = separateStringForVector(addPlayerInfosTextBox->toPlainText().toStdString());
    db.addPlayerToDatabase(addPlayerInDbBox->currentText().toStdString(), addPlayerPlayerName->text().toStdString(), addPlayerPlayerInfos);
    deleteAddPlayer();
    addPlayerInDB();
}

void seeOptionsWindow::deleteAddPlayer()
{
    addPlayerRequestBox->close();
    delete addPlayerRequestBox, addPlayerInDbBox, addPlayerInDbOk, addPlayerInDbCancel, addPlayerInfosTextBox, addPlayerPlayerName;
}


void seeOptionsWindow::rmPlayerFromDB()
{
    rmPlayerRequestBox = new QDialog(this);
    rmPlayerRequestBox->setFixedSize(500, 300);
    rmPlayerRequestBox->setWindowTitle("Remove a player from database :");

    std::vector<std::string> availableDatabases = getAllAvailableDatabases();
    rmPlayerFromDbBox = new QComboBox(rmPlayerRequestBox);
    rmPlayerFromDbBox->setGeometry(40, 170, 150, 25);
    for (int i = 0; i < availableDatabases.size(); i++)
    {
        rmPlayerFromDbBox->addItem(availableDatabases[i].c_str());
    }
    rmPlayerFromDbBox->setCurrentText(getSelectedDatabase().c_str());
    rmPlayerFromDbBox->show();

    std::vector<std::string> playersInDatabase = db.getAllAvailablePlayersInDatabase(rmPlayerFromDbBox->currentText().toStdString());
    rmPlayerFromDbName = new QComboBox(rmPlayerRequestBox);
    rmPlayerFromDbName->setGeometry(300, 170, 150, 25);
    for (int i = 0; i < playersInDatabase.size(); i++)
    {
        rmPlayerFromDbName->addItem(playersInDatabase[i].c_str());
    }
    rmPlayerFromDbName->show();

    addPlayerInDbOk = new QPushButton("Ok", rmPlayerRequestBox);
    addPlayerInDbOk->setGeometry(100, 240, 50, 25);

    addPlayerInDbCancel = new QPushButton("Cancel", rmPlayerRequestBox);
    addPlayerInDbCancel->setGeometry(350, 240, 50, 25);

    QObject::connect(addPlayerInDbOk, SIGNAL(clicked()), this, SLOT(rmPlayer()));
    QObject::connect(addPlayerInDbCancel, SIGNAL(clicked()), this, SLOT(deleteRmPlayer()));
    QObject::connect(rmPlayerFromDbBox, SIGNAL(currentTextChanged(QString)), this, SLOT(reloadRmPlayerFromDbName(QString)));

    rmPlayerRequestBox->exec();
}

void seeOptionsWindow::rmPlayer()
{
    db.removePlayerFromDatabase(rmPlayerFromDbBox->currentText().toStdString(), rmPlayerFromDbName->currentText().toStdString());
    deleteRmPlayer();
    rmPlayerFromDB();
}

void seeOptionsWindow::deleteRmPlayer()
{
    rmPlayerRequestBox->close();
    delete rmPlayerRequestBox, rmPlayerFromDbBox, rmPlayerFromDbName, rmPlayerFromDbOk, rmPlayerFromDbCancel;
}

void seeOptionsWindow::reloadRmPlayerFromDbName(QString Str)
{
    rmPlayerFromDbName->hide();
    std::vector<std::string> playersInDatabase = db.getAllAvailablePlayersInDatabase(rmPlayerFromDbBox->currentText().toStdString());
    rmPlayerFromDbName = new QComboBox(rmPlayerRequestBox);
    rmPlayerFromDbName->setGeometry(300, 180, 200, 25);
    for (int i = 0; i < playersInDatabase.size(); i++)
    {
        rmPlayerFromDbName->addItem(playersInDatabase[i].c_str());
    }
    rmPlayerFromDbName->show();
}



void seeOptionsWindow::setDatabase(QString QStr)
{
    setSelectedDatabase(QStr.toStdString());
}

void seeOptionsWindow::returnMainMenuFromOptions()
{
    close();
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
}

std::vector<std::string> seeOptionsWindow::separateStringForVector(std::string str)
{
    std::vector<std::string> vector;
    std::string delimiter = "\n", token;
    size_t pos = 0;
    
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        vector.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    vector.push_back(str);
    return vector;
}
