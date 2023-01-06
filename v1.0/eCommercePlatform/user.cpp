#include "user.h"
#include<fstream>

User::User()
{
    this->type = 0;
}

void User::setUser(QString username,QString userpassword,double userbalance,bool usertype)
{
    this->username = username;
    this->password = userpassword;
    this->balance = userbalance;
    this->type = usertype;
}
bool User::getUserType() const
{
    return this->type;
}
