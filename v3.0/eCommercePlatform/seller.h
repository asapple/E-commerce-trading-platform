#ifndef SELLER_H
#define SELLER_H
#include"user_virtual.h"
class seller : public user_virtual //商家类
{
public:
    void setUser(QString username,QString userpassword,double userbalance,bool usertype);
    bool getUserType() const;
    seller();
};

#endif // SELLER_H
