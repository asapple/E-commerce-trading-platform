#ifndef WIDGETMENU_H
#define WIDGETMENU_H

#include <QWidget>
#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QTimer>
#include<cstring>
#include<iostream>
#include<fstream>
#include"user.h"
#include"additems.h"
#include"changepassword.h"
#include"edititem.h"
namespace Ui {
class WidgetMenu;
}

class WidgetMenu : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMenu(QWidget *parent = 0);
    User user1;
    QSqlTableModel *model;
    QSqlTableModel *modelcart;
    AddItems *wadditems;
    changepassword *wcp;
    edititem *editit;
    ~WidgetMenu();

    void unlogin_set();//游客登录不可编辑
private slots:


    void on_pushButtonRefresh_clicked();

    void on_pushButtonAddItems_clicked();

    void on_pushButtonInfo_clicked();

    void on_pushButtonPassword_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButtonedititem_clicked();

    void on_pushButtonMoney_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtoncleancart_clicked();

    void on_pushButtonaddcart_clicked();

    void on_pushButtonbuy_clicked();

private:
    Ui::WidgetMenu *ui;
    void changeBalance(const QString userName,const double newBalance);

};

#endif // WIDGETMENU_H
