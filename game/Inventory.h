#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <vector>

#include "PartsFactory.h"
#include "WeaponFactory.h"
#include "../graphics/PopUpMenu.h"

inline wConfigs ASSAULTRIFLE = { 10, 10, 10, 100, 10, 10, 10, 10, 10 };

// TODO: Make this into a template or something cause this is ass.
typedef struct InventorySlots
{
    std::vector<Part> Parts;
    std::vector<Weapon> Weapons;
} InvSlots;

class Inventory
{
    public:
        int InventorySize_;
        int InventorySlotsLeft_;
        std::vector<InvSlots> Inventory_;

        void generateInventory(int inventorySize) {
            PartsFactory partsfactory;
            WeaponFactory wf;
            InvSlots tempInvSlots;
            std::vector<Part> tempParts;
            std::vector<Weapon> tempWeapons;

            this->InventorySize_ = inventorySize;
            this->InventorySlotsLeft_ = inventorySize;
            this->Inventory_.reserve(inventorySize);

            // Creating one of each type of part and storing it in a temp parts buffer.
            for (int i = HEAD; i != LEGS+1; i++) {
                if (this->InventorySlotsLeft_ == 0) {
                    std::cout << "Inventory Full!" << std::endl;
                    break;
                } else {
                    tempParts.push_back(partsfactory.CreatePart(static_cast<PartType>(i)));
                    this->InventorySlotsLeft_--;
                }
            }

            // Create a couple weapons and storing it a temp weapon buffer.
            for (int j = 0; j != 3; j++) {
                if (this->InventorySlotsLeft_ == 0) {
                    std::cout << "Inventory Full!" << std::endl;
                    break;
                } else {
                    tempWeapons.push_back(wf.CreateWeapon(RIFLE, ASSAULTRIFLE, "Assault Rifle", "Dev", "An assault rifle...yeah."));
                    this->InventorySlotsLeft_--;
                }
            }

            // Allocate the parts and weapons to a temp InvSlots buffer.
            tempInvSlots.Parts = tempParts;
            tempInvSlots.Weapons = tempWeapons;
            
            // Set the inventory with the items.
            this->Inventory_.push_back(tempInvSlots);
        };

};

#endif // INVENTORY_CLASS_H