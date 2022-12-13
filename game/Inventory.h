#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <variant>
#include <vector>

#include "PartsFactory.h"
#include "WeaponFactory.h"
#include "../graphics/PopUpMenu.h"
#include "../util/NameGenerator.h"

inline wConfigs ASSAULTRIFLE = { 10, 10, 10, 100, 10, 10, 10, 10, 10 };

class Inventory
{
    public:
        int InventorySize_;
        int InventorySlotsLeft_;
        std::vector<Part> inventoryParts_;
        std::vector<Weapon> inventoryWeapons_;

        void generateInventory(int inventorySize) {
            PartsFactory pf;
            WeaponFactory wf;

            this->InventorySize_ = inventorySize;
            this->InventorySlotsLeft_ = inventorySize;

            // Creating one of each type of part and adding it to the inventory if it is not full.
            for (auto pT: allPartTypes) {
                if (this->InventorySlotsLeft_ == 0) {
                    std::cout << "Inventory Full!" << std::endl;
                    break;
                } else {
                    this->inventoryParts_.push_back(pf.CreatePart(pT));
                    this->InventorySlotsLeft_--;
                }
            }

            // Create a couple weapons and storing it a temp weapon buffer.
            for (auto wT: testWeaponTypes) {
                if (this->InventorySlotsLeft_ == 0) {
                    std::cout << "Inventory Full!" << std::endl;
                    break;
                } else {
                    this->inventoryWeapons_.push_back(wf.CreateWeapon(wT, CreateRandomWeaponConfigs(), RandomString(), "Dev", "Test Weapon"));
                    this->InventorySlotsLeft_--;
                }
            }

            std::cout << "Weapon Inventory: " << this->inventoryWeapons_.at(0).Name << std::endl;
        };

};

#endif // INVENTORY_CLASS_H