#include <iostream>

#include "Mech_Factory.h"

Frame dev_mech_frame_init()
{
    // Dev_mech
    Defenses frameOneDefenses;
    frameOneDefenses.ballisticDefense = 10;
    frameOneDefenses.energyDefense = 10;
    Frame frameOne("Frame One", "Developer", "Dev1", 1, 1, frameOneDefenses);

    return frameOne;
}
