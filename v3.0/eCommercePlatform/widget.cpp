#include "widget.h"
#include "ui_widget.h"
#include"mysql.h"
#include<QDebug>
#include<QString>
#include<QMessageBox>
#include"send_info.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //从注册页面返回的操作
    this->setWindowTitle("欢迎");
    wRegister = new widgetRegister;
    wMenu = new WidgetMenu;
    connect(this->wRegister,&widgetRegister::widgetRegisterBack,
            [=](){
        wRegister->close();
        this->show();
    });
    //方便测试
    ui->lineEditUserName->setText("cwjcwj");
    ui->lineEditPassword->setText("123456789");

    Connect();//建立TCP连接
}

Widget::~Widget()
{
    delete ui;
}
//跳转到注册页面的操作
void Widget::on_pushButtonRegister_clicked()
{
    this->hide();
    this->wRegister->show();
}
//跳转到菜单页面
extern QTcpSocket *tcpsock;
void Widget::on_pushButtonLogin_clicked()
{
    struct net_info tmp_data;
    tmp_data.info_type = "Login";
    tmp_data.username = ui->lineEditUserName->text();
    tmp_data.password = ui->lineEditPassword->text();
    Send(tmp_data);

    if(tcpsock->waitForReadyRead(3000))
    {
        QByteArray array = tcpsock->readAll();
        QString info = QString(array);
        struct net_ret d = breakup2handle(info);
        if(d.ack == "yes")
        {
            this->wMenu->user1.setUser(ui->lineEditUserName->text(),ui->lineEditPassword->text(),d.balance.toDouble(),d.type.toInt());
            this->hide();
            this->wMenu->show();
        }
        else
        {
            QMessageBox::warning(this,"error"
                                 ,QString("账号密码出错"));
        }
    }
}
int Widget::findUser()
{
    qDebug()<<"findUser";
    std::string _username,_userpassword;
    double _userbalance;
    bool _usertype;
    std::ifstream userfile;
    userfile.open("../../day01/user.txt",std::ios::in);
    if(userfile == NULL)
    {
        QMessageBox::warning(this,"error"
                                         ,QString("文件打开失败"));
        return 0;
    }
    while(userfile >>_username>>_userpassword>>_userbalance>>_usertype)
    {
        qDebug()<<QString::fromStdString(_username);
        qDebug()<<QString::fromStdString(_userpassword);
        qDebug()<<_userbalance;
        qDebug()<<_usertype;
        if(QString::fromStdString(_username) == ui->lineEditUserName->text())
        {
            if(QString::fromStdString(_userpassword) == ui->lineEditPassword->text())
            {
                this->wMenu->user1.setUser(QString::fromStdString(_username),QString::fromStdString(_userpassword),_userbalance,_usertype);
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    userfile.close();
    return -1;
}

void Widget::on_pushButton_clicked()
{
    this->hide();
    this->wMenu->show();
    this->wMenu->unlogin_set();
}
