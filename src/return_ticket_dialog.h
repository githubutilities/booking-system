#ifndef RETURN_TICKET_DIALOG_H
#define RETURN_TICKET_DIALOG_H

#include <QDialog>
#include "MyFlightBookingSystem.h"
#include "MyFlight.h"
namespace Ui {
class return_ticket_dialog;
}

class return_ticket_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit return_ticket_dialog(QWidget *parent = 0);
    ~return_ticket_dialog();

    void setSystem(MyFlightBookingSystem *sys);
private slots:
    void on_returnBt_clicked();

private:
    Ui::return_ticket_dialog *ui;
    MyFlightBookingSystem * system;
    bool validQuery(string &q);
};

#endif // RETURN_TICKET_DIALOG_H
