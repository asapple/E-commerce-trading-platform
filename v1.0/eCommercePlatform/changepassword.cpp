#include "changepassword.h"
#include "ui_changepassword.h"
#include<QMessageBox>
#include<fstream>
#include<iostream>
#include<QMessageBox>
changepassword::changepassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);
    this->setWindowTitle("修改密码");
}

changepassword::~changepassword()
{
    delete ui;
}

void changepassword::on_pushButton_clicked()
{
    std::string password=ui->lineEditnew->text().toStdString();
    if(password.length()<6 || password.length()>18)
    {
        QMessageBox::warning(this,"error"
                             ,QString("密码长度不符合规范"));
        return ;
    }
    for(unsigned int i=0; i<password.length(); i++)
    {
        if(( password[i]>='a'&&password[i]<='z' ) || ( password[i]>='A'&&password[i]<='Z' ) || ( password[i]>='0'&&password[i]<='9' ))
            continue;
        else
        {
            QMessageBox::warning(this,"error"
                                 ,QString("密码字符仅包括大写小写字母和数字"));
            return ;
        }
    }
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
        if(tmp == username.toStdString()&&i%4==1)
        {
            getline(userfile,tmp);
            str.append(password).append("\n");
        }
    }
    userfile.close();
    std::fstream userout;
    userout.open("../user.txt",std::ios::out);
    userout << str;
    userout.close();
    QMessageBox::warning(this,"成功","密码修改成功");
    this->close();
}
