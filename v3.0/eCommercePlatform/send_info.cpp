#include"send_info.h"


QString gather2send(struct net_info data)
{
    QString tmp = data.info_type + "\n" +data.username + "\n" + data.password + "\n"+data.type+"\n";
    return tmp;
}

QTcpSocket *tcpsock = NULL;
void Connect()
{
    tcpsock = new QTcpSocket(NULL);
    QString ip = "127.0.0.1";
    qint16 port = 8888;
    tcpsock->connectToHost(QHostAddress(ip),port);
}
void Send(struct net_info data)
{
    tcpsock->write(gather2send(data).toUtf8().data());
}

void Break()
{
    tcpsock->disconnectFromHost();
    tcpsock->close();
}
#include<sstream>
struct net_ret breakup2handle(QString data)
{
    struct net_ret d;
    std::string tmp_ack,tmp_balance,tmp_type;
    std::istringstream is(data.toStdString());
    is>>tmp_ack>>tmp_balance>>tmp_type;
    d.ack = QString::fromStdString(tmp_ack);
    d.balance = QString::fromStdString(tmp_balance);
    d.type = QString::fromStdString(tmp_type);
    return d;
}
