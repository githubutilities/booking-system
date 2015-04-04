#ifndef BUY_DIALOG_H
#define BUY_DIALOG_H

#include <QDialog>
#include "MyFlight.h"
#include "MyFlightBookingSystem.h"
namespace Ui {
class buy_dialog;
}

class buy_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit buy_dialog(QWidget *parent = 0);
    ~buy_dialog();
    void setFlight(MyFlightBookingSystem *sys, MyFlight * wanted);

private slots:
    void on_buyBt_clicked();

private:
    Ui::buy_dialog *ui;
    MyFlight *want;
    MyFlightBookingSystem *system;
    bool validQuery(string &q);
};

#endif // BUY_DIALOG_H
