#include "buy_ticket.h"
#include "ui_buy_ticket.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>

buy_ticket::buy_ticket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buy_ticket)
{
    idxSelect = -1; selected = false;
    cad = new MyVector<MyFlight *>;
    ui->setupUi(this);
}

buy_ticket::~buy_ticket()
{
    delete ui;
}

void buy_ticket::setSystem(MyFlightBookingSystem *sys) {
    system = sys;
}


void buy_ticket::on_queryBt_clicked()
{
    ui->queryBt->blockSignals(true);
    selected = false;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    string q = ui->queryLn->text().toStdString();

    MyVector<MyFlight *> &ret = *cad;
    ret.clear();

    std::cout << q << std::endl;
    if(system->queryByFlightID(q, ret)){
        string tmp = string(
                    QString::fromUtf8("目的地\t起飞时间\t航班\t飞机号").
                    toUtf8()
                    );
        QStringList list;
        list += QString::fromUtf8(tmp.c_str());

        for (int i = 0; i < ret.size(); i++) {
            string ans = ret[i]->getDest(); ans += "\t";
            ans += ret[i]->getDate(); ans += "\t";
            ans += ret[i]->getFlightID(); ans += "\t";
            ans += ret[i]->getPlaneID();
            list += QString::fromUtf8(ans.c_str());
            ret[i]->write(std::cout);
        }
        QStringListModel *model = new QStringListModel(list);
        ui->listView->setModel(model);
    } else {
        QMessageBox mess;
        mess.setWindowTitle("没找到");
        mess.setText("没找到!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
    }
    ui->queryBt->blockSignals(false);
}

void buy_ticket::on_queryLn_editingFinished()
{

}

void buy_ticket::on_listView_clicked(const QModelIndex &index)
{
    idxSelect = index.row(); selected = true;
}

void buy_ticket::on_buyBt_clicked()
{
    if(!selected && 0 != idxSelect) {
        QMessageBox mess;
        mess.setWindowTitle("请选择航班");
        mess.setText("请选择航班!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }
    MyVector<MyFlight *> &ret = *cad;
    buy_dialog *wid = new buy_dialog();
    wid->setFlight(system, ret[idxSelect - 1]);
    wid->show();
  //  ret[idxSelect - 1]->write(std::cout);
}
