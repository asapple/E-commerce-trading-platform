#ifndef ITEMS_VIRTUAL_H
#define ITEMS_VIRTUAL_H
#include<QString>
class items_virtual //商品基类
{
public:
    int id;
    QString type;//商品类型
    QString name;//
    QString introduce;
    int number;
    int ordered;
    double price;
    double discount;
    QString owner;
    virtual double getPrice() const = 0;
private:
};
#endif // ITEMS_VIRTUAL_H
