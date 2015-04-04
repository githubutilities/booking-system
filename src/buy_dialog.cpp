#include "buy_dialog.h"
#include "ui_buy_dialog.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <string>
buy_dialog::buy_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buy_dialog)
{
    ui->setupUi(this);
}

buy_dialog::~buy_dialog()
{
    delete ui;
}

void buy_dialog::setFlight(MyFlightBookingSystem *sys, MyFlight *wanted) {
    system = sys; want = wanted;
}


void buy_dialog::on_buyBt_clicked()
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

    QString innum = ui->tickNum->text();
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
    std::cout << num << endl;

    if (!num) {
        QMessageBox mess;
        mess.setWindowTitle("不合法数目");
        mess.setText("不能为零!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
        return;
    }

    int ret = system->book(username, want, num);
    if(BOOK_SUCCESS == ret) {
        QMessageBox mess;
        mess.setWindowTitle("购买成功");
        mess.setText("购买成功!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
    } else if (INVALID_TICKET_NUM == ret) {
        QMessageBox mess;
        mess.setWindowTitle("购买失败");
        mess.setText("购买票数超过总座位!");
        mess.setStandardButtons(QMessageBox::Yes);
        if(mess.exec() == QMessageBox::Yes) mess.close();
    } else {
        QMessageBox mess;
        mess.setWindowTitle("购买失败");
        mess.setText("座位不够，是否排队等待？");
        mess.setStandardButtons(QMessageBox::Yes);
        mess.setStandardButtons(QMessageBox::No);
        if(mess.exec() == QMessageBox::Yes) {
            system->joinQueue(username, want, num);
            mess.close();
        } else {
            mess.close();
        }
    }
}

bool buy_dialog::validQuery(string &q) {
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
