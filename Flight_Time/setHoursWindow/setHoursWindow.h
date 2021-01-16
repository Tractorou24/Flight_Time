#ifndef SETHOURSWINDOW_H
#define SETHOURSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <vector>
#include "../seeOptionsWindow/database.h"

class setHoursWindow : public QDialog
{
    Q_OBJECT

public:
    setHoursWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void validateInformations();
    void returnMainMenuFromSetHours();
    void updateNameCheckBoxes(QString selectedDB);

signals:
    void close_me();

private:
    void createNameCheckBoxes(std::string databaseName);
    std::vector<std::string> getCheckedNameCheckBoxs();
    void deleteNameCheckBoxes(std::string databaseName);

    void createChoiceCheckBox();
    std::vector<std::string> getCheckedChoiceCheckBox();
    void deleteChoiceCkeckBox();

    void createHoursBoxes();
    void deleteHoursBoxes();

    std::map<std::string, QCheckBox*> checkBoxes;
    std::map<std::string, QCheckBox*> flightCheckBoxes;
    std::map<std::string, QLineEdit*> hoursTextBoxes;

    database db;

    QComboBox* selectedDBBox;
    QPushButton* returnMain, *validate;
};

#endif