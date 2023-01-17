#ifndef MECHFACTORY_H
#define MECHFACTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "PartsFactory.h"
#include "WeaponFactory.h"
#include "../util/Maths.h"
#include "../util/enumFactory.h"
#include "../graphics/PopUpMenu.h"

/**
 * @brief This is will hold the parts of the mech. Will serve sort of as a blank template.
 * 
 */
class Frame
{
    public:
        std::string Name_;

        // Only here to satisfy frame class being inherited by Mech class.
        Frame() {};

        Frame(std::string Name) : Name_(Name) {}
};

/**
 * @brief Creates a Mech.
 * 
 */
class Mech : public Frame
{
    private:

        bool checkIfFullyEquipped() {
            if (!this->head_.Name.empty() && !this->core_.Name.empty() && !this->arms_.Name.empty() && !this->legs_.Name.empty()) {
                this->fullyEquipped_ = true;
                return true;
            }
            
            return false;
        };

    public:
        Part head_, core_, arms_, legs_;
        Weapon leftArmWeapon_, rightArmWeapon_, leftShoulderWeapon_, rightShoulderWeapon_;
        Frame frame_;
        // TODO: Make mechslots that show if equiped or not for the weapons.
        std::string Name_;
        unsigned int level_;
        unsigned int totalAP_;
        unsigned int currentAP_;
        bool fullyEquipped_;

        // Used to create an empty blank template.
        Mech() { this->totalAP_ = 0; this->currentAP_ = 0; }; // FIXME: Have to zero initialize these for some reason...

        // Custom Mech constructor that allocates all the necessary components for quick creation.
        Mech(std::string Name, Frame frame, Part Head, Part Core, Part Arms, Part Legs) :
            Name_(Name), frame_(frame), head_(Head), core_(Core), arms_(Arms), legs_(Legs)
        {
            std::cout << "Creating Mech..." << std::endl;
            this->SetName(Name);
            this->SetLevel(0);
            this->fullyEquipped_ = false;
            this->leftArmWeapon_.Equipped=false;
            this->rightArmWeapon_.Equipped=false;
            this->totalAP_ = this->CalculateTotalAP(); // TODO: Make this just automatically set the total and currernt AP.
            this->currentAP_ = this->CalculateTotalAP();
        };

        bool checkIfSlotIsFull(PartType pType) {
            switch (pType) {
                case HEAD:
                    if (this->head_.Name.empty())
                        return false;
                    return true;
                    break;
                case CORE:
                    if (this->core_.Name.empty())
                        return false;
                    return true;
                    break;
                case ARMS:
                    if (this->arms_.Name.empty())
                        return false;
                    return true;
                    break;
                case LEGS:
                    if (this->legs_.Name.empty())
                        return false;
                    return true;
                    break;
                default:
                    std::cout << "Could not decipher part type for checking mech slot." << std::endl;
                    break;
            }
            return true; // Incase the switch statement breaks; return true to stop anything from propogating.
        };

        void SetName(std::string Name) {
            this->Name_ = Name;
        };

        void SetLevel(unsigned int Level) {
            this->level_ = Level;
        };

        void BindFrame(Frame frame) {
            this->frame_ = frame;
        };

        void EquipHead(Part Head) {
            if (!checkIfSlotIsFull(HEAD)) {
                this->head_ = Head;
                this->totalAP_ = CalculateTotalAP();
                this->currentAP_ = CalculateTotalAP();
            }
            this->head_.Initialized = true;
            checkIfFullyEquipped();
        };

        void EquipCore(Part Core) {
            if (!checkIfSlotIsFull(CORE)) {
                this->core_ = Core;
                this->totalAP_ = CalculateTotalAP();
                this->currentAP_ = CalculateTotalAP();
            }
            this->core_.Initialized = true;
            checkIfFullyEquipped();
        };

        void EquipArms(Part Arms) {
            if (!checkIfSlotIsFull(ARMS)) {
                this->arms_ = Arms;
                this->totalAP_ = CalculateTotalAP();
                this->currentAP_ = CalculateTotalAP();
            }
            this->arms_.Initialized = true;
            checkIfFullyEquipped();
        };

        void EquipLegs(Part Legs) {
            if (!checkIfSlotIsFull(LEGS)) {
                this->legs_ = Legs;
                this->totalAP_ = CalculateTotalAP();
                this->currentAP_ = CalculateTotalAP();
            }
            this->legs_.Initialized = true;
            checkIfFullyEquipped();
        };

        void EquipLeftArmWeapon(Weapon weapon) {
            this->leftArmWeapon_ = weapon;
            this->leftArmWeapon_.Equipped = true;
            this->leftArmWeapon_.Initialized = true;
            std::cout << "Equipped Left Arm Weapon." << std::endl;
        };

        void EquipRightArmWeapon(Weapon weapon) {
            this->rightArmWeapon_ = weapon;
            this->rightArmWeapon_.Equipped = true;
            this->rightArmWeapon_.Initialized = true;
            std::cout << "Equipped Right Arm Weapon." << std::endl;
        };

        void EquipLeftShoulderWeapon(Weapon weapon) {
            this->leftShoulderWeapon_ = weapon;
            this->leftShoulderWeapon_.Equipped = true;
            this->leftShoulderWeapon_.Initialized =true;
            std::cout << "Equipped Left Shoulder Weapon." << std::endl;
        };

        void EquipRightShoulderWeapon(Weapon weapon) {
            this->rightShoulderWeapon_ = weapon;
            this->rightShoulderWeapon_.Equipped = true;
            this->rightShoulderWeapon_.Initialized = true;
            std::cout << "Equipped Right Shoulder Weapon." << std::endl;
        };

        void SetTotalAP(unsigned int ArmorPoints) {
            this->totalAP_ = ArmorPoints;
        };

        void SetCurrentAP(unsigned int ArmorPoints) {
            this->currentAP_ = ArmorPoints;
        };

        unsigned int CalculateTotalAP() {
            unsigned int temp = 0;
            if (!head_.Name.empty()) temp += head_.ArmorPoints; else temp += 0;
            if (!core_.Name.empty()) temp += core_.ArmorPoints; else temp += 0;
            if (!arms_.Name.empty()) temp += arms_.ArmorPoints; else temp += 0;
            if (!legs_.Name.empty()) temp += legs_.ArmorPoints; else temp += 0;
            return temp;
        };


};

Frame FrameInit();
Mech MechInit();

#endif // MECHFACTORY_H