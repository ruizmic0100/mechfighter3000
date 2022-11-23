#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <vector>

#include "Items.h"

class Inventory
{
    public:
        int inventorySlots;
        std::vector<Item> Items;

        Inventory() {

        }
};

#endif // INVENTORY_CLASS_H