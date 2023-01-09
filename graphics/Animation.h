#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Model.h"

void translateModelOverADistance(Shader& shader, Camera& camera, Model& model, glm::vec3 endLocation);



#endif // ANIMATION_SYSTEM_H