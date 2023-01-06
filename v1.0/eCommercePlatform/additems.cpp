#include "additems.h"
#include "ui_additems.h"

#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>

AddItems::AddItems(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddItems)
{
    ui->setupUi(this);
    this->setWindowTitle("添加商品");
}

AddItems::~AddItems()
{
    delete ui;
}

void AddItems::on_pushButtonadd_clicked()
{
    QSqlQuery query;
    QString type = ui->comboBox->currentText();
    QString name = ui->lineEditname->text();
    QString introduce=ui->textEditintroduce->toPlainText();
    int number = ui->lineEditnumber->text().toInt();
    double price = ui->lineEditprice->text().toDouble();
    double discount = 10;
    QString owner = this->username;
    QString tmp = QString("insert into items(type,name,introduce,number,price,discount,owner) values('"+type+"','"+name+"','"+introduce+"',%1,%2,%3,'"+owner+"')").arg(number).arg(price).arg(discount);
    query.exec(tmp);
    QMessageBox::warning(this,"成功","添加成功!!");
    this->hide();
}
