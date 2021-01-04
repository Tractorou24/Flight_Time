#ifndef SEEOPTIONSWINDOW_H
#define SEEOPTIONSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
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
    void rmPlayerFromDB();
    void returnMainMenuFromOptions();
    void setDatabase(QString QStr);

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
};

#endif
