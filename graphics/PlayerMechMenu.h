#ifndef PLAYER_MECHMENU_CLASS_H
#define PLAYER_MECHMENU_CLASS_H

#include <iostream>
#include <string>

#include "menu/imguipp.h"
#include "menu/Settings.h"

#include "../game/Player.h"
#include "../game/Enemy.h"


extern bool isOpen, showInventory, showAlreadyEquippedPopUp, ChangeLightColor;

void Theme();
void Render(Player& player, Enemy& enemy, unsigned int menu_textures);
void CustomRendering();

#endif // PLAYER_MECHMENU_CLASS_H