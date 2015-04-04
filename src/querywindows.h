#ifndef QUERYWINDOWS_H
#define QUERYWINDOWS_H

#include <QDialog>
#include "MyFlightBookingSystem.h"
#include "MyFlight.h"
#include "MyVector.h"
#include <string>
#include <iostream>
#include <QMessageBox>
namespace Ui {
class QueryWindows;
}

class QueryWindows : public QDialog
{
    Q_OBJECT

public:
    explicit QueryWindows(QWidget *parent = 0);
    ~QueryWindows();

    void setSystem(MyFlightBookingSystem * sys);
private slots:
    void on_queryBt_clicked();

    void on_queryBox_editingFinished();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::QueryWindows *ui;
    MyFlightBookingSystem *system;
    bool validQuery(string &q);
};

#endif // QUERYWINDOWS_H
