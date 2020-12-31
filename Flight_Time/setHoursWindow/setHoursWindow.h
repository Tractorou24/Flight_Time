#ifndef SETHOURSWINDOW_H
#define SETHOURSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>

class setHoursWindow : public QDialog
{
    Q_OBJECT

public:
    setHoursWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void returnMainMenuFromSetHours();

signals:
    void close_me();

private:
    QPushButton* returnMain;
};

#endif