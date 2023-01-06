#ifndef ITEMS_BOOK_H
#define ITEMS_BOOK_H
#include"items_virtual.h"
class items_book : public items_virtual
{
public:
    items_book();
    double getPrice() const;
};

#endif // ITEMS_BOOK_H
