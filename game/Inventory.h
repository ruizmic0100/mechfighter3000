#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <vector>

#include "PartsFactory.h"

class Inventory
{
    public:
        int inventorySlots_;
        std::vector<Part> Inventory_;

        void generateInventory(int invSlots) {
            PartsFactory partsfactory;
            this->inventorySlots_ = invSlots;

            // Creating one of each type of part and storing it in the inventory:
            Inventory_.push_back(partsfactory.CreatePart(HEAD));
            Inventory_.push_back(partsfactory.CreatePart(CORE));
            Inventory_.push_back(partsfactory.CreatePart(ARMS));
            Inventory_.push_back(partsfactory.CreatePart(LEGS));
        }
};

#endif // INVENTORY_CLASS_H