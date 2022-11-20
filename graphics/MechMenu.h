#ifndef MECHMENU_CLASS_H
#define MECHMENU_CLASS_H

#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "../game/Mech_Factory.h"
#include "../game/Player.h"

inline bool isOpen, showInventory;

void MechMenu(Player* player);

#endif // MECHMENU_CLASS_H