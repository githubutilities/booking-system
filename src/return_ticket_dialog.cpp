#include "return_ticket_dialog.h"
#include "ui_return_ticket_dialog.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <string>
return_ticket_dialog::return_ticket_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::return_ticket_dialog)
{
    ui->setupUi(this);
}

return_ticket_dialog::~return_ticket_dialog()
{
    delete ui;
}

void return_ticket_dialog::setSystem(MyFlightBookingSystem *sys) {
    system = sys;
}

bool return_ticket_dialog::validQuery(string &q) {
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

void return_ticket_dialog::on_returnBt_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString inusername = ui->username->text();
    QByteArray data = inusername.toUtf8();
    string username = string(data.data());
    if(!validQuery(username)) {
        QMessageBox mess;
        mess.setWindowTitle("不合法用户名");
        mess.setText("请输入正确的用户名!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }
    std::cout << username << std::endl;

    QString inFlightID = ui->flightID->text();
    string flightID = inFlightID.toStdString();
    if(!validQuery(flightID)) {
        QMessageBox mess;
        mess.setWindowTitle("不合法航班号");
        mess.setText("请输入正确的航班号!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }
    std::cout << flightID << std::endl;

    QString indate = ui->year->text() + "." +
            ui->month->text() + "." + ui->day->text();
    if (ui->year->text() > "9999" || ui->year->text() < "1000" ||
            ui->month->text().toInt() < 1 || ui->month->text().toInt() > 12 ||
            ui->day->text().toInt() < 1 || ui->day->text().toInt() > 31) {
        QMessageBox mess;
        mess.setWindowTitle("不合法日期");
        mess.setText("请输入正确的日期!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }
    string date = indate.toStdString();
    std::cout << date << std::endl;

    QString innum = ui->ticketNum->text();
    string ticknum = innum.toStdString();
    std::cout << ticknum << std::endl;
    bool valid = true;
    for (int i = 0; i < ticknum.size(); i++)
        if(ticknum[i] > '9' || ticknum[i] < '0') valid = false;
    if((ticknum.size() > 3 || ticknum.size() == 0) || false == valid) {
        QMessageBox mess;
        mess.setWindowTitle("不合法数目");
        mess.setText("请输入整数!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }
    int num = 0;
    for (int i = 0; i < ticknum.size(); i++)
        num *= 10, num += ticknum[i] - '0';
    std::cout << num << std::endl;

    if (!num) {
        QMessageBox mess;
        mess.setWindowTitle("不合法数目");
        mess.setText("不能为零!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }

    MyVector<MyFlight*> ret;
    ret.clear();
    bool find = false;
    find = system->queryByFlightID(flightID, ret);
    if(find) {
        int i;
        for ( i = 0; i < ret.size(); i++) {
            if(ret[i]->getDate() == date) break;
        }
        if(ret.size() == i) find = false;
        else {
            int rr = system->returnTicket(username, ret[i], num);
            if(INVALID_TICKET_NUM == rr) {
                QMessageBox mess;
                mess.setWindowTitle("错误");
                mess.setText("退票数目不能超过购买数目!");
                mess.setStandardButtons(QMessageBox::Yes);
                if(mess.exec() == QMessageBox::Yes) mess.close();
                return;
            } else if (CUSTOMER_NOT_FOUND == rr) find = false;
            else {
                QMessageBox mess;
                mess.setWindowTitle("退票成功");
                mess.setText("退票成功!");
                mess.setStandardButtons(QMessageBox::Yes);
                if(mess.exec() == QMessageBox::Yes) mess.close();
                return;
            }
        }
        if(find) return;
    }
    if(!find){
        QMessageBox mess;
        mess.setWindowTitle("没找到");
        mess.setText("没找到相关航班!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
    }
}
