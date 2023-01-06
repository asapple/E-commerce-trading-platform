#ifndef ITEMS_ELECT_H
#define ITEMS_ELECT_H
#include"items_virtual.h"
class items_elect : public items_virtual
{
public:
    items_elect();
    double getPrice() const;
};

#endif // ITEMS_ELECT_H
