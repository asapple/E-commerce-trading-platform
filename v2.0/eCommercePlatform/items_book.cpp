#include "items_book.h"

items_book::items_book()
{
    this->type = "纸质书";
}
double items_book::getPrice() const{
    return this->price;
}
