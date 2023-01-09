#ifndef ENEMY_MENU_H
#define ENEMY_MENU_H

#include <iostream>

#include "./menu/Settings.h"

#include "../game/Player.h"
#include "../game/Enemy.h"

namespace BattleMenu
{
    extern bool isOpen;
    void BattleMenu(Player& player, Enemy& enemy);
}


#endif // ENEMY_MENU_H