#include "Mech_Factory.h"
// TODO: Make a mech setup checker.

Frame FrameInit()
{
    // Empty Dev Frame.
    Frame devFrame("Developer Frame");

    return devFrame;
}

Mech MechInit()
{
    // Empty Dev Mech.
    Mech devMech;

    // NOTE: Initial Construction Requirements.
    devMech.SetName("Dev Mech");
    devMech.SetLevel(0);
    devMech.BindFrame(FrameInit());
    devMech.fullyEquipped_ = false;
    devMech.CalculateTotalAP();

    return devMech;
}
