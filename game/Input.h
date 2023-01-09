#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "RenderList.h"

class Input
{
    public:
        // Stores the recent inputs by the player that aren't movement/looking.
        std::vector<int> playerInputs_;

        void Inputs(GLFWwindow* window) {
            if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
                renderPlayerMechMenu = true;
            }
        }
};

#endif // INPUT_CLASS_H