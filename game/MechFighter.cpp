#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <GLFW/glfw3.h>

#include "../graphics/renderer.h"
#include "../util/logging.h"

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
    std::string Name_;
    std::string Manufacturer_;
    std::string Identifier_;
    int Price_;
    int Weight_;
    Defenses Defenses_;

    public:
        Frame(std::string frameName, std::string frameManufacturer, std::string frameIdentifier, int framePrice, int frameWeight, Defenses frameDefenses) :
                Name_(frameName), Manufacturer_(frameManufacturer), Identifier_(frameIdentifier), Price_(framePrice), Weight_(frameWeight), Defenses_(frameDefenses) {
            Log("Creating Frame:");
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





int main(void)
{
    OutputDebugStringW(L"Test\n");
    // Test Run
    Defenses frameOneDefenses;
    frameOneDefenses.ballisticDefense = 10;
    frameOneDefenses.energyDefense = 10;
    Frame frameOne("Frame One", "Developer", "Dev1", 1, 1, frameOneDefenses);

    renderer(); // Initializes the renderer.
    GLuint test = 3;

}
