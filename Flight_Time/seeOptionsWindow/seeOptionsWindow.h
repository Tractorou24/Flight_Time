#ifndef SEEOPTIONSWINDOW_H
#define SEEOPTIONSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>

class seeOptionsWindow : public QDialog
{
    Q_OBJECT

public:

    seeOptionsWindow(QWidget* parent = Q_NULLPTR);
private slots:
    void returnMainMenuFromOptions();

signals:
    void close_me();

private:
    QPushButton* returnMain;
};

#endif
