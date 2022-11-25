#ifndef MECHFACTORY_H
#define MECHFACTORY_H

#include <iostream>
#include <vector>
#include <string>

#include "PartsFactory.h"

struct Stats
{
    int health;
};

struct Defenses
{
    int ballisticDefense;
    int energyDefense;
};


struct Shoulder
{

};

struct Core
{
    
};

struct Arms
{

};

struct Legs
{

};


class Frame
{
    public:
        std::string Name_;
        std::string Manufacturer_;
        std::string Identifier_;
        int Price_;
        int Weight_;
        Defenses Defenses_;

        // Only here to satisfy frame class being inherited by Mech class.
        Frame() {}

        Frame(std::string frameName, std::string frameManufacturer, std::string frameIdentifier, int framePrice, int frameWeight, Defenses frameDefenses) :
                Name_(frameName), Manufacturer_(frameManufacturer), Identifier_(frameIdentifier), Price_(framePrice), Weight_(frameWeight), Defenses_(frameDefenses) {
        }
};

class Mech : public Frame
{
    public:
        Part head_, rightShoulder_, leftShoulder_, core_, arms_, legs_;

        Mech(Part Head, Part RightShoulder, Part LeftShoulder, Part Core, Part Arms, Part Legs) :
            head_(Head), rightShoulder_(RightShoulder), leftShoulder_(LeftShoulder), core_(Core), arms_(Arms), legs_(Legs)
        {
            std::cout << "Creating Mech..." << std::endl;
        
        };
};

Frame* dev_mech_frame_init();

#endif // MECHFACTORY_H