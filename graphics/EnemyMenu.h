#ifndef ENEMY_MENU_H
#define ENEMY_MENU_H

#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "../game/Player.h"
#include "../game/Enemy.h"


void EnemyMenu(Enemy enemy);

#endif // ENEMY_MENU_H