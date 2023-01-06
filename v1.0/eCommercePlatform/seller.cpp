#include "seller.h"

seller::seller()
{
    this->type = 1;
}
void seller::setUser(QString username,QString userpassword,double userbalance,bool usertype)
{
    this->username = username;
    this->password = userpassword;
    this->balance = userbalance;
    this->type = usertype;
}
bool seller::getUserType() const
{
    return this->type;
}
