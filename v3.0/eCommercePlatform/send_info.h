#ifndef SEND_INFO_H
#define SEND_INFO_H
#include<QTcpSocket>
#include<QHostAddress>
#include<QString>
struct net_info{
    QString info_type;
    QString username;
    QString password;
    QString type;
};
struct net_ret{
    QString ack;
    QString balance;
    QString type;
};
void Connect();
void Send(struct net_info data);
void Break();
QString gather2send(struct net_info data);
struct net_ret breakup2handle(QString info);
#endif // SEND_INFO_H
