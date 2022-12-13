#ifndef ENEMY_MENU_H
#define ENEMY_MENU_H

#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "MechMenu.h"
#include "../game/Player.h"
#include "../game/Enemy.h"
#include "./menu/Settings.h"

void EnemyMenu(Player& player, Enemy& enemy);

#endif // ENEMY_MENU_H