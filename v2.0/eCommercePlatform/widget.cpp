#include "widget.h"
#include "ui_widget.h"
#include"mysql.h"
#include<QDebug>
#include<QString>
#include<QMessageBox>
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
void Widget::on_pushButtonLogin_clicked()
{
    if(findUser() == 1)
    {
        this->hide();
        this->wMenu->show();
    }
    else
    {
        QMessageBox::warning(this,"error"
                             ,QString("账号密码出错"));
    }
}
int Widget::findUser()
{
    qDebug()<<"findUser";
    std::string _username,_userpassword;
    double _userbalance;
    bool _usertype;
    std::ifstream userfile;
    userfile.open("../user.txt",std::ios::in);
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
