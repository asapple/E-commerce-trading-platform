#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>//监听套接字
#include<QTcpSocket>//通信套接字
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

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void handle_info();
    struct net_info breakup2handle(QString info);
    void Send(struct net_ret data);
    QString gather2send(struct net_ret data);
private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonBreak_clicked();
private:
    Ui::Widget *ui;

    QTcpServer *tcpServer = NULL;
    QTcpSocket *tcpSocket = NULL;
};

#endif // WIDGET_H
