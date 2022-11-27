#ifndef MECHFACTORY_H
#define MECHFACTORY_H

#include <iostream>
#include <vector>
#include <string>

#include "PartsFactory.h"
#include "../util/Maths.h"

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
        void checkIfFullyEquipped() {
            if (!this->head_.Name.empty() && !this->core_.Name.empty() && !this->arms_.Name.empty() && !this->legs_.Name.empty())
                this->fullyEquipped_ = true;
        };

    public:
        Part head_, core_, arms_, legs_;
        Frame frame_;
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
            this->SetLevel(getRand() / 10000);
            this->fullyEquipped_ = false;
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
            this->head_ = Head;
            checkIfFullyEquipped();
            this->totalAP_ = CalculateTotalAP();
            this->currentAP_ = CalculateTotalAP();
        };

        void EquipCore(Part Core) {
            this->core_ = Core;
            checkIfFullyEquipped();
            this->totalAP_ = CalculateTotalAP();
            this->currentAP_ = CalculateTotalAP();
        };

        void EquipArms(Part Arms) {
            this->arms_ = Arms;
            checkIfFullyEquipped();
            this->totalAP_ = CalculateTotalAP();
            this->currentAP_ = CalculateTotalAP();
        };

        void EquipLegs(Part Legs) {
            this->legs_ = Legs;
            checkIfFullyEquipped();
            this->totalAP_ = CalculateTotalAP();
            this->currentAP_ = CalculateTotalAP();
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