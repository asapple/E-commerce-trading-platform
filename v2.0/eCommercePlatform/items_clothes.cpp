#include "items_clothes.h"

items_clothes::items_clothes()
{
    this->type = "服饰";
}
double items_clothes::getPrice() const{
    return this->price;
}
