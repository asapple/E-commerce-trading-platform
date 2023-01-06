#ifndef USER_VIRTUAL_H
#define USER_VIRTUAL_H
#include<QString>
class user_virtual //用户基类
{
public:
    virtual void setUser(QString username,QString userpassword,double userbalance,bool usertype) = 0;
    virtual bool getUserType() const = 0;
    QString username;//账号名
    QString password;//密码
    double balance;//余额
    bool type;//账户类型：商家/消费者

private:
};
#endif // USER_VIRTUAL_H
