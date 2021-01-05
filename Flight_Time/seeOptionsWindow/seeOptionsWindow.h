#ifndef SEEOPTIONSWINDOW_H
#define SEEOPTIONSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <vector>
#include "database.h"

class seeOptionsWindow : public QDialog
{
    Q_OBJECT

public:
    seeOptionsWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void addDB();
    void createDB();
    void deleteCreateDB();

    void rmDB();
    void deleteDB();
    void deleteDeleteDB();

    void addPlayerInDB();
    void addPlayer();
    void deleteAddPlayer();

    void rmPlayerFromDB();
    void rmPlayer();
    void deleteRmPlayer();
    void reloadRmPlayerFromDbName(QString Str);

    void returnMainMenuFromOptions();
    void setDatabase(QString QStr);
    std::vector<std::string> separateStringForVector(std::string str);

signals:
    void close_me();

private:
    QLabel* label;
    QPixmap* pixmap_img;
    QGridLayout* gridLayout;

    QComboBox* selectedDBBox;

    QPushButton* returnMain;
    QPushButton* addDatabase;
    QPushButton* removeDatabase;
    QPushButton* addPlayerinSelectedDatabase;
    QPushButton* removePlayerFromSelectedDatabase;

    database db;

    //ADD DB
    QDialog* AddDbRequestBox;
    QLineEdit* AddDbDbName;
    QPushButton* AddDbOk;
    QPushButton* AddDbCancel;

    //RM DB
    QDialog* RmDbRequestBox;
    QComboBox* rmDbBox;
    QPushButton* RmDbOk;
    QPushButton* RmDbCancel;

    //ADD PLAYER
    QDialog* addPlayerRequestBox;
    QComboBox* addPlayerInDbBox;
    QPushButton* addPlayerInDbOk;
    QPushButton* addPlayerInDbCancel;
    QTextEdit* addPlayerInfosTextBox;
    QLineEdit* addPlayerPlayerName;
    std::vector<std::string> addPlayerPlayerInfos;

    //RM PLAYER
    QDialog* rmPlayerRequestBox;
    QComboBox* rmPlayerFromDbBox;
    QComboBox* rmPlayerFromDbName;
    QPushButton* rmPlayerFromDbOk;
    QPushButton* rmPlayerFromDbCancel;
};

#endif
