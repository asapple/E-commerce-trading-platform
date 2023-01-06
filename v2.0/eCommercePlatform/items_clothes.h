#ifndef ITEMS_CLOTHES_H
#define ITEMS_CLOTHES_H
#include"items_virtual.h"
class items_clothes : public items_virtual
{
public:
    items_clothes();
    double getPrice() const;
};

#endif // ITEMS_CLOTHES_H
