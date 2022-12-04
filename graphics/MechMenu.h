#ifndef MECHMENU_CLASS_H
#define MECHMENU_CLASS_H

#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "../game/Mech_Factory.h"
#include "../game/Player.h"
#include "../game/GameEventHandler.h"
#include "../game/Enemy.h"
#include "menu/imguipp.h"
#include "menu/Settings.h"

inline bool isOpen, showNewMechMenu, showInventory, showEnemyWindow, showAlreadyEquippedPopUp;

void RenderMechMenu(Player& player, Enemy& enemy);

namespace MechMenu
{
    void Theme();
    void Render();
}

#endif // MECHMENU_CLASS_H