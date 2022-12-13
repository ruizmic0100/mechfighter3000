#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>

#include "Inventory.h"
#include "Mech_Factory.h"

// TODO: Make this dynamic so we don't get out of range errors.
#define PLAYER_MAX_INVENTORY_SLOTS 7

class Player {
    public:
        Mech playerMech;
        Inventory PlayerInventory;
        
        Player() {
            this->PlayerInventory.generateInventory(PLAYER_MAX_INVENTORY_SLOTS);
            std::cout << "Player Initialized." << std::endl;
        };

        // NOTE: Why is this not in the constructor?
        void BindMech(Mech mech) {
            this->playerMech = mech;
        };
};

Player PlayerInit();

void EquipPart(Part partToEquip, Player& player);


#endif // PLAYER_CLASS_H