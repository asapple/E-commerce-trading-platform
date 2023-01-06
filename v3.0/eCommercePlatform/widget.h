#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"widgetregister.h"
#include"widgetmenu.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //在文件中寻找用户名为this->username，找到返回1，没找到返回-1
    int findUser();
    //注册页面
    widgetRegister *wRegister = NULL;
    //菜单页面
    WidgetMenu *wMenu = NULL;

private slots:
    //注册
    void on_pushButtonRegister_clicked();
    //登录
    void on_pushButtonLogin_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
