#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <vector>

#include "PartsFactory.h"

class Inventory
{
    public:
        int inventorySlots_;
        std::vector<Part> Parts_;

        void generateInventory(int invSlots) {
            PartsFactory partsfactory;
            this->inventorySlots_ = invSlots;

            for (int i = 0; i < invSlots; i++) {
                Parts_.push_back(partsfactory.CreatePart());
            }
        }
};

#endif // INVENTORY_CLASS_H