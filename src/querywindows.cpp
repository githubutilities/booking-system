#include "querywindows.h"
#include "ui_querywindows.h"

#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QStringListModel>
#include <QStringList>
#include <QTextCodec>
QueryWindows::QueryWindows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryWindows)
{
    ui->setupUi(this);
}

QueryWindows::~QueryWindows()
{
    delete ui;
}

void QueryWindows::setSystem(MyFlightBookingSystem *sys) {
    system = sys;
}

void QueryWindows::on_queryBt_clicked()
{
    ui->queryBt->blockSignals(true);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString str = ui->queryBox->text();
    QByteArray data = str.toUtf8();

    string q = string(data.data());
    if(validQuery(q)) {
        MyVector<MyFlight *> ret;
        ret.clear();

        if(system->queryByDest(q, ret)){
            QStringList list;\
            string tmp = string(
                        QString::fromUtf8("目的地\t起飞时间\t航班\t飞机号").
                        toUtf8()
                        );
            list += QString::fromUtf8(tmp.c_str());
            //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
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
    } else {
        QMessageBox mess;
        mess.setWindowTitle("不合法索引");
        mess.setText("请输入正确的字符串!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
    }
    ui->queryBt->blockSignals(false);
}

void QueryWindows::on_queryBox_editingFinished()
{
    /*
    ui->queryBox->blockSignals(true);
    on_queryBt_clicked();
    ui->queryBox->blockSignals(false);
    */
}

bool QueryWindows::validQuery(string &q) {
    if(q.size() == 0) return false;
    bool ret = false;
    for (int i = 0; i < (int)q.size(); i++)
        if(isblank(q[i]) == 0) ret = true;
    if(ret) {
        int i = 0, j = q.size() - 1;
        for (; isblank(q[i]); i++);
        for (; isblank(q[j]); j--);
        q = q.substr(i, j - i + 1);
    }
    return ret;
}

void QueryWindows::on_listView_clicked(const QModelIndex &index)
{
    std::cout << index.row() << std::endl;
}
