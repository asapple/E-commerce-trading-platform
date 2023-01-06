#include "items_elect.h"

items_elect::items_elect()
{
    this->type = "电子产品";
}
double items_elect::getPrice() const{
    return this->price;
}
