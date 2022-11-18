#include <iostream>

struct Stats
{
    int health;
};

struct Defenses
{
    int ballisticDefense;
    int energyDefense;
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

        Frame(std::string frameName, std::string frameManufacturer, std::string frameIdentifier, int framePrice, int frameWeight, Defenses frameDefenses) :
                Name_(frameName), Manufacturer_(frameManufacturer), Identifier_(frameIdentifier), Price_(framePrice), Weight_(frameWeight), Defenses_(frameDefenses) {
            listFrameSpecs();
        }

        void listFrameSpecs() {
            std::cout << "Name: " << Name_ << std::endl;
            std::cout << "Manufacturer: " << Manufacturer_ << std::endl;
            std::cout << "Identifier: " << Identifier_ << std::endl;
            std::cout << "Price: " << Price_ << std::endl;
            std::cout << "Weight: " << Weight_ << std::endl;
            std::cout << "Defenses: " << "[BD] " << Defenses_.ballisticDefense << " [ED] " << Defenses_.energyDefense << std::endl;
        }
};

class Mech : public Frame
{

    public:
};

Frame dev_mech_frame_init();