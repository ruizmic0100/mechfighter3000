#include "Player.h"

Player* PlayerInit()
{
    // Set up inventory:
    std::cout << "Player Init Started" << std::endl;
    Inventory playerInventory;

    // Set up Mech:
    Player* player = new Player;
    player->SetFrame(dev_mech_frame_init());
    return player;
}