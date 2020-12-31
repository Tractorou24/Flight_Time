#ifndef SEEHOURSWINDOW_H
#define SEEHOURSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>

class seeHoursWindow : public QDialog
{
    Q_OBJECT

public:
    seeHoursWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void returnMainMenuFromSeeHours();

signals:
    void close_me();

private:
    QPushButton* returnMain;
};

#endif
        
