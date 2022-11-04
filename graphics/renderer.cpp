#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// Vertices coordinates.
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner.
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner.
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f   // Upper corner.
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left.
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right.
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};

GLuint indices[] =
{
    0, 3, 5, // Lower left triangle.
    3, 2, 4, // Lower right triangle.
    5, 4, 1  // Upper triangle.
};

/**
 * @brief Steps taken to render the window.
 * 
 * @return
 */
int renderer()
{
    // Initialize the library.
    if (!glfwInit())
        return -1;
    
    // Tell GLFW major and minor version, and to use core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a windowed mode window and its OpenGL context.
    GLFWwindow* window = glfwCreateWindow(800, 800, "MechFighter3000", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current:
    glfwMakeContextCurrent(window);

    // Load GLAD so it configure opengl.
    gladLoadGL();

    // Specifying the viewport:
    glViewport(0, 0, 800, 800);


    // Generates Shader object using shaders default.vert and default.frag:
    Shader shaderProgram("graphics/shaders/default.vert", "graphics/shaders/default.frag");

    // Generates Vertex Array Object and binds it:
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex buffer object and links it to vertices:
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element buffer object and links it to indices:
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    // Unbind all to prevent accidentally modifying them:
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which shader program we want to use:
        shaderProgram.Activate();
        // Bind the VAO so OpenGL knows to use it:
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}