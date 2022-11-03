#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <GLFW/glfw3.h>

#include "renderer.h"

int renderer()
{
    GLFWwindow* window;

    // Initialize the library.
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context.
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current.
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window.
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the front and back buffers:
        glfwSwapBuffers(window);

        // Poll for and process events:
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}