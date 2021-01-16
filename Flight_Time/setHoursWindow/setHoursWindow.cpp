#include <QApplication>
#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <iostream>
#include "../mainWindow/mainWindow.h"
#include "../general/programSettings.h"
#include "../setHoursWindow/setHoursWindow.h"

setHoursWindow::setHoursWindow(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(1280, 720);

    // Selected Database Box
    std::vector<std::string> availableDatabases = getAllAvailableDatabases();
    selectedDBBox = new QComboBox(this);
    selectedDBBox->setGeometry(1050, 20, 200, 25);
    for (int i = 0; i < availableDatabases.size(); i++)
    {
        selectedDBBox->addItem(availableDatabases[i].c_str());
    }
    selectedDBBox->setCurrentText(getSelectedDatabase().c_str());
    selectedDBBox->show();

    createNameCheckBoxes((selectedDBBox->currentText()).toStdString());
    createChoiceCheckBox();
    createHoursBoxes();

    db.addAnHourInDatabase("VF84", "200 Bullit", "allTime", 2.0);
    db.addAnHourInDatabase("VF84", "206 Orion", "allTime", 2.0);

    // Buttons
    validate = new QPushButton("Valider", this);
    validate->setGeometry(0, 670, 100, 50);
    
    returnMain = new QPushButton("Retour", this);
    returnMain->setGeometry(1180, 670, 100, 50);

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(validateInformations()));
    QObject::connect(returnMain, SIGNAL(clicked()), this, SLOT(returnMainMenuFromSetHours()));
    QObject::connect(selectedDBBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateNameCheckBoxes(QString)));
}

void setHoursWindow::validateInformations() {
    std::vector<std::string> playersChecked = getCheckedNameCheckBoxs();
    std::vector<std::string> activitiesChecked = getCheckedChoiceCheckBox();
    
    for (int i = 0; i < playersChecked.size(); i++) {
        for (int j = 0; j < activitiesChecked.size(); j++) {
            db.addADateInDatabase((selectedDBBox->currentText()).toStdString(), playersChecked[i], activitiesChecked[j], db.getNewDate());
        }
        for (auto& [key, value] : hoursTextBoxes) {
            if (value->isModified()) {
                db.addAnHourInDatabase((selectedDBBox->currentText()).toStdString(), playersChecked[i], key, value->text().toDouble());
            }
        }
    }
    returnMainMenuFromSetHours();
}

void setHoursWindow::returnMainMenuFromSetHours()
{
    close();
    deleteNameCheckBoxes((selectedDBBox->currentText()).toStdString());
    deleteChoiceCkeckBox();
    deleteHoursBoxes();
    delete returnMain, selectedDBBox;

    emit close_me();
}


void setHoursWindow::createNameCheckBoxes(std::string databaseName)
{
    // Check boxes
    std::vector<std::string> players = db.getAllAvailablePlayersInDatabase(databaseName);
    int j = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (i < 24) {
            checkBoxes[players[i]] = new QCheckBox(players[i].c_str(), this);
            checkBoxes[players[i]]->setGeometry(25, 25 * i + 20, 100, 25);
            checkBoxes[players[i]]->show();
        }
        else if (i < 48) {
            checkBoxes[players[i]] = new QCheckBox(players[i].c_str(), this);
            checkBoxes[players[i]]->setGeometry(125, 25 * j + 20, 100, 25);
            checkBoxes[players[i]]->show();
            j++;
        }
        else {
            // TOO MANY PLAYERS
        }
    }
}

std::vector<std::string> setHoursWindow::getCheckedNameCheckBoxs()
{
    std::vector<std::string> checkedBoxes;
    for (auto& [key, value] : checkBoxes) {
        if (value->isChecked()) {
            checkedBoxes.push_back(key);
        }
    }
    return checkedBoxes;
}

void setHoursWindow::deleteNameCheckBoxes(std::string databaseName)
{
    std::vector<std::string> players = db.getAllAvailablePlayersInDatabase(databaseName);
    for (int i = 0; i < players.size(); i++)
    {
        delete checkBoxes[players[i]];
    }
}

void setHoursWindow::updateNameCheckBoxes(QString selectedDB)
{
    deleteNameCheckBoxes(getSelectedDatabase());
    setSelectedDatabase(selectedDB.toStdString());
    createNameCheckBoxes(selectedDB.toStdString());
}


void setHoursWindow::createChoiceCheckBox()
{
    flightCheckBoxes["caseIDeparture"] = new QCheckBox("Depart Case 1", this);
    flightCheckBoxes["caseIIorIIIDeparture"] = new QCheckBox("Depart Case II / III", this);
    flightCheckBoxes["caseIArrival"] = new QCheckBox("Arrivee Case 1", this);
    flightCheckBoxes["caseIIorIIIArrival"] = new QCheckBox("Arrivee Case II / III", this);
    flightCheckBoxes["bvr"] = new QCheckBox("BVR", this);
    flightCheckBoxes["bfm"] = new QCheckBox("BFM", this);
    flightCheckBoxes["AAGuns"] = new QCheckBox("A/A Guns", this);
    flightCheckBoxes["intercept"] = new QCheckBox("Interception", this);
    flightCheckBoxes["dayAAR"] = new QCheckBox("Ravitaillemnt de jour", this);
    flightCheckBoxes["nightAAR"] = new QCheckBox("Ravitaillemnt de nuit", this);
    flightCheckBoxes["laserGuidedBombs"] = new QCheckBox("Bombes Guidees Laser", this);
    flightCheckBoxes["unguidedBombs"] = new QCheckBox("Bombes non guidees", this);
    flightCheckBoxes["tald"] = new QCheckBox("Tald", this);
    flightCheckBoxes["rockets"] = new QCheckBox("Roquettes", this);
    flightCheckBoxes["AGGuns"] = new QCheckBox("A/G Guns", this);
    flightCheckBoxes["tacturn"] = new QCheckBox("Tacturns", this);
    flightCheckBoxes["training"] = new QCheckBox("Training", this);
    flightCheckBoxes["missions"] = new QCheckBox("Missions", this);

    int i = 0;
    for (auto& [key, value] : flightCheckBoxes) {
        flightCheckBoxes[key]->setGeometry(800, 25*i+50, 200, 25);
        flightCheckBoxes[key]->show();
        i++;
    }
}

std::vector<std::string> setHoursWindow::getCheckedChoiceCheckBox()
{
    std::vector<std::string> checkedBoxes;
    for (auto& [key, value] : flightCheckBoxes) {
        if (flightCheckBoxes[key]->isChecked()) {
            checkedBoxes.push_back(key);
        }
    }
    return checkedBoxes;
}

void setHoursWindow::deleteChoiceCkeckBox()
{
    for (auto& [key, value] : flightCheckBoxes) {
        delete flightCheckBoxes[key];
    }

    flightCheckBoxes.clear();
}


void setHoursWindow::createHoursBoxes()
{
    hoursTextBoxes["allTime"] = new QLineEdit(this);
    hoursTextBoxes["dayTime"] = new QLineEdit(this);
    hoursTextBoxes["nightTime"] = new QLineEdit(this);
    hoursTextBoxes["instrumentsTime"] = new QLineEdit(this);
    hoursTextBoxes["totalAA"] = new QLineEdit(this);
    hoursTextBoxes["totalAG"] = new QLineEdit(this);

    int i = 0;
    for (auto& [key, value] : hoursTextBoxes) {
        hoursTextBoxes[key]->setGeometry(500, 25 * i + 50, 200, 25);
        hoursTextBoxes[key]->setPlaceholderText(QString::fromUtf8(key.c_str()));
        hoursTextBoxes[key]->show();
        i++;
    }
}

void setHoursWindow::deleteHoursBoxes()
{
    for (auto& [key, value] : hoursTextBoxes) {
        delete hoursTextBoxes[key];
    }

    hoursTextBoxes.clear();
}