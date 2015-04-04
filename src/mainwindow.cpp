#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    system = new MyFlightBookingSystem();
    fio = new std::fstream("in.txt", std::ios::in | std::ios::out);
    system->init(*fio);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    system->write(*fio);
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QueryWindows *wid = new QueryWindows();
    wid->setSystem(system);
    wid->show();
    /*
    QLabel *label = new QLabel(QString("请输入航班号"));
    QLineEdit *edit = new QLineEdit();
    QPushButton *bt = new QPushButton("查询");
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(edit);
    layout->addWidget(bt);
    QWidget *queryWid = new QWidget();
    queryWid->setLayout(layout);
    queryWid->show();*/
}

void MainWindow::on_pushButton_2_clicked()
{
    buy_ticket *wid = new buy_ticket();
    wid->setSystem(system);
    wid->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    fio->close();
    delete fio;
    fio = new std::fstream("in.txt",std::ios::out);
    //system->write(*fio);
    this->close();
}

void MainWindow::on_returnBt_clicked()
{
    return_ticket_dialog *wid = new return_ticket_dialog();
    wid->setSystem(system);
    wid->show();
}
