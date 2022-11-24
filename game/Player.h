#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>

#include "Mech_Factory.h"
#include "Inventory.h"

#define PLAYER_MAX_INVENTORY_SLOTS 5

class Player {
    public:
        Frame* equippedFrame;
        Mech* equippedMech;
        Inventory PlayerInventory;
        
        Player() {
            this->PlayerInventory.generateInventory(PLAYER_MAX_INVENTORY_SLOTS);
            std::cout << "Player Initialized." << std::endl;
        };

        void SetFrame(Frame* frame) {
            this->equippedFrame = frame;
            std::cout << "Frame: " << this->equippedFrame->Name_ << std::endl;
        };
};

Player* PlayerInit();


#endif // PLAYER_CLASS_H