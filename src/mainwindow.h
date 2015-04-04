#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
#include <iostream>
#include <QMainWindow>
#include "MyFlightBookingSystem.h"
#include "querywindows.h"
#include "buy_ticket.h"
#include "return_ticket_dialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_returnBt_clicked();

private:
    Ui::MainWindow *ui;
    MyFlightBookingSystem *system;
    std::fstream *fio;
};

#endif // MAINWINDOW_H
