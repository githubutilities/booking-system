#ifndef BUY_TICKET_H
#define BUY_TICKET_H

#include <QDialog>
#include "buy_dialog.h"
#include "MyFlightBookingSystem.h"

namespace Ui {
class buy_ticket;
}

class buy_ticket : public QDialog
{
    Q_OBJECT

public:
    explicit buy_ticket(QWidget *parent = 0);
    ~buy_ticket();

    void setSystem(MyFlightBookingSystem *sys);
private slots:

    void on_queryBt_clicked();

    void on_queryLn_editingFinished();

    void on_listView_clicked(const QModelIndex &index);

    void on_buyBt_clicked();

private:
    Ui::buy_ticket *ui;
    MyFlightBookingSystem *system;
    bool selected; int idxSelect;
    MyVector<MyFlight *> *cad;
};

#endif // BUY_TICKET_H
