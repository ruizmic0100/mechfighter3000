#include "Mech_Factory.h"

Frame* dev_mech_frame_init()
{
    // Dev_mech
    Defenses devFrameDefenses;
    devFrameDefenses.ballisticDefense = 10;
    devFrameDefenses.energyDefense = 10;
    Frame* devFrame = new Frame("Developer Frame", "Developer", "Devie", 1, 1, devFrameDefenses);

    return devFrame;
}
