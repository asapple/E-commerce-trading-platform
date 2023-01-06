#ifndef USER_H
#define USER_H

#include<QString>
#include"user_virtual.h"
class User:public user_virtual //消费者类
{
public:
    User();
    void setUser(QString username,QString userpassword,double userbalance,bool usertype);
    bool getUserType() const;
private:
};

#endif // USER_H
