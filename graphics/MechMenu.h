#ifndef MECHMENU_CLASS_H
#define MECHMENU_CLASS_H

#include <iostream>
#include <string>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "../game/Mech_Factory.h"
#include "../game/Player.h"
#include "../game/GameEventHandler.h"
#include "../game/Enemy.h"
#include "EnemyMenu.h"
#include "menu/imguipp.h"
#include "menu/Settings.h"

inline bool isOpen, showNewMechMenu, showInventory, showAlreadyEquippedPopUp;

extern float progress, armorPointsBar;

namespace MechMenu
{
    void Theme();
    void Render(Player& player, Enemy& enemy);
    void CustomRendering();
}

#endif // MECHMENU_CLASS_H