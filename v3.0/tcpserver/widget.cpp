#include "widget.h"
#include "ui_widget.h"
#include<sstream>
#include<iostream>
#include<string.h>
#include<fstream>
#include<QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("TcpServer");
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any
                      ,8888);
    connect(tcpServer,&QTcpServer::
            newConnection,[=](){
        tcpSocket = tcpServer->
                nextPendingConnection();
        QString ip = tcpSocket->peerAddress()
                .toString();
        qint16 port = tcpSocket->peerPort();
        QString temp = QString("与[%1:%2]成功连接").arg(ip).arg(port);
        ui->textEditRead->append(temp);

        connect(tcpSocket,&QTcpSocket::readyRead,
                [=](){
            handle_info();
        });
        connect(tcpSocket,&QTcpSocket::disconnected,
                [=](){
           ui->textEditRead->append("与客户端断开连接");
        });
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonSend_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    QString str = ui->textEditWrite->
            toPlainText();
    tcpSocket->write(str.toUtf8().data());

}

void Widget::on_pushButtonBreak_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket = NULL;
}
void Widget::handle_info()
{
    QByteArray array = tcpSocket->readAll();
    ui->textEditRead->append(array);
    QString info = QString(array);
    struct net_info d = breakup2handle(info);

    if(d.info_type == "Login")
    {
        ui->textEditWrite->append("findUser:");
        std::string _username,_userpassword;
        double _userbalance;
        bool _usertype;
        std::ifstream userfile;
        userfile.open("../user.txt",std::ios::in);
        if(userfile == NULL)
        {
            QMessageBox::warning(this,"error"
                                             ,QString("文件打开失败"));
            return;
        }
        while(userfile >>_username>>_userpassword>>_userbalance>>_usertype)
        {
            if(QString::fromStdString(_username) == d.username)
            {
                if(QString::fromStdString(_userpassword) == d.password)
                {
                    struct net_ret r;
                    r.ack = "yes";
                    r.balance=QString::number(_userbalance);
                    r.type =QString::number(_usertype);
                    Send(r);
                    return ;
                }
                else
                {
                    struct net_ret r;
                    r.ack = "no";
                    Send(r);
                    return ;
                }
            }
        }
        userfile.close();
        struct net_ret r;
        r.ack = "no";
        Send(r);
        return ;
    }
    else if(d.info_type == "Reg")
    {
        ui->textEditWrite->append("newUser:");
        double balance = 0;
        std::ofstream myfile("../user.txt",std::ios::app);
        if(myfile == NULL)
        {
            QMessageBox::warning(this,"error"
                                             ,QString("文件打开失败"));
        }
        myfile << d.username.toStdString() << "\n";
        myfile << d.password.toStdString() << "\n";
        myfile << balance << "\n";
        myfile << d.type.toStdString() << "\n";
        myfile.close();
    }else if(d.info_type =="changePassword")
    {
        std::fstream userfile;
        userfile.open("../user.txt",std::ios::in);
        if(userfile == NULL)
        {
            QMessageBox::warning(this,"error"
                                             ,QString("文件打开失败"));
        }
        std::string str,tmp;
        int i=0;
        while(getline(userfile,tmp))
        {
            i++;
            str.append(tmp).append("\n");
            if(tmp == d.username.toStdString()&&i%4==1)
            {
                getline(userfile,tmp);
                str.append(d.password.toStdString()).append("\n");
            }
        }
        userfile.close();
        std::fstream userout;
        userout.open("../user.txt",std::ios::out);
        userout << str;
        userout.close();
    }else if(d.info_type =="addbalance")
    {
        std::fstream userfile;
        userfile.open("../user.txt",std::ios::in);
        std::string str,tmp;
        int i=0;
        while(getline(userfile,tmp))
        {
            i++;
            str.append(tmp).append("\n");
            if(tmp == d.username.toStdString()&&i%4==1)
            {
                getline(userfile,tmp);
                str.append(tmp).append("\n");
                getline(userfile,tmp);

                double newbalance = QString::fromStdString(tmp).toDouble() + d.password.toDouble();
                str.append((QString::number(newbalance)).toStdString()).append("\n");
            }
        }
        userfile.close();
        std::fstream userout;
        userout.open("../user.txt",std::ios::out);
        userout << str;
        userout.close();
    }else if(d.info_type =="subbalance")
    {
        std::fstream userfile;
        userfile.open("../user.txt",std::ios::in);
        std::string str,tmp;
        int i=0;
        while(getline(userfile,tmp))
        {
            i++;
            str.append(tmp).append("\n");
            if(tmp == d.username.toStdString()&&i%4==1)
            {
                getline(userfile,tmp);
                str.append(tmp).append("\n");
                getline(userfile,tmp);

                double newbalance = QString::fromStdString(tmp).toDouble() - d.password.toDouble();
                str.append((QString::number(newbalance)).toStdString()).append("\n");
            }
        }
        userfile.close();
        std::fstream userout;
        userout.open("../user.txt",std::ios::out);
        userout << str;
        userout.close();
    }

}
struct net_info Widget::breakup2handle(QString info)
{
    struct net_info d;
    std::string tmp_info_type,tmp_username,tmp_password,tmp_type;
    std::istringstream is(info.toStdString());
    is>>tmp_info_type>>tmp_username>>tmp_password>>tmp_type;
    d.info_type = QString::fromStdString(tmp_info_type);
    d.username = QString::fromStdString(tmp_username);
    d.password = QString::fromStdString(tmp_password);
    d.type = QString::fromStdString(tmp_type);
    return d;
}
void Widget::Send(struct net_ret data)
{
    ui->textEditWrite->append(gather2send(data));
    tcpSocket->write(gather2send(data).toUtf8().data());
}
QString Widget::gather2send(struct net_ret data)
{
    QString tmp = data.ack+"\n"+data.balance+"\n"+data.type+"\n";
    return tmp;
}
