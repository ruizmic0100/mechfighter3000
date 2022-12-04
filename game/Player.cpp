#include "Player.h"

/**
 * @brief 
 * @note You have to create the player before you can create the mech...meh.
 * The reason why is because you need to have an inventory of parts first before they can
 * be equipped. Might want to create an invisible inventory for the already equipped mech parts
 * and have that be put into the inventory afterwards...
 * 
 * @return Player
 */
Player PlayerInit()
{
    std::cout << "Player Init Started" << std::endl;
    // When player created: 
    //      1. Inventory is generated.
    Player player;

    // Binding the Mech and player together.
    player.BindMech(MechInit());

    return player;
}

void EquipPart(Part partToEquip, Player& player)
{
    std::cout << "Trying to Equip Part: " << partToEquip.Name.c_str() << std::endl;
    switch (partToEquip.Type) {
        case HEAD:
            player.playerMech.EquipHead(partToEquip);
            break;
        case CORE:
            player.playerMech.EquipCore(partToEquip);
            break;
        case ARMS:
            player.playerMech.EquipArms(partToEquip);
            break;
        case LEGS:
            player.playerMech.EquipLegs(partToEquip);
            break;
        default:
            std::cout << "Couldn't decipher part type to equip!" << std::endl;
            break;
    }
}