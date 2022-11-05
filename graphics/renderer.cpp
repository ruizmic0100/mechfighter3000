#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../stb/stb_image.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "renderer.h"
#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates.
GLfloat vertices[] =
{   //  COORDINATES      /  COLORS          /       TexCoord //
    -0.5f, -0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f, // Lower left corner.
    -0.5f,  0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f, // Lower right corner.
     0.5f,  0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f, // Upper corner.
     0.5f,  0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f, // Inner left.
     0.0f,  0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     2.5f, 5.0f  // Inner left.
};

GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
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
    GLFWwindow* window = glfwCreateWindow(width, height, "MechFighter3000", NULL, NULL);
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
    glViewport(0, 0, width, height);


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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them:
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // Texture relative path.
    std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    std::string texPath = "/build/graphics/assets/";

    // Texture:
    Texture spaceShipTexture((parentDir + texPath + "spaceship_texture.jpg").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    spaceShipTexture.texUnit(shaderProgram, "tex0", 0);


    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Tell OpenGL which shader program we want to use:
        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Binds texture so that it appears in rendering:
        spaceShipTexture.Bind();
        // Bind the VAO so OpenGL knows to use it:
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    spaceShipTexture.Delete();
    shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}