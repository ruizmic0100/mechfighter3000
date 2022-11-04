#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

// Vertex shader source code.
const char* vertexShaderSource = R"myDelim(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    })myDelim";

// Fragment shader source code.
const char* fragmentShaderSource = R"myDelim(
    #version 330 core

    out vec4 FragColor;
    
    void main()
    {
        FragColor = vec4(0.4f, 0.67f, 0.02f, 1.0f);
    }\n)myDelim";

/**
 * @brief Steps taken to render the window.
 * 
 * @return
 */
int renderer()
{
    GLFWwindow* window;

    // Initialize the library.
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a windowed mode window and its OpenGL context.
    window = glfwCreateWindow(640, 480, "MechFighter3000", NULL, NULL);
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
    glViewport(0, 0, 640, 480);
    
    // Create Vertex Shader Object and get reference:
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source to the vertex shader object:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the vertex shader into machine code:
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get reference:
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source to the fragment shader object:
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the fragment shader into machine code:
    glCompileShader(fragmentShader);

    // Create shader program object and get it's reference:
    GLuint shaderProgram = glCreateProgram();
    // Attach the vertex and fragment shaders to the shader program:
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/link all the shaders together into the shader program:
    glLinkProgram(shaderProgram);

    // Delete the now useless shaders:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Vertices coordinates.
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower left corner.
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   // Lower right corner.
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner.
    };

    // Create reference containers for the vertex array object and the vertex buffer object:
    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each:
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current vertex array object by binding it:
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER:
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO:
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // COnfigure the vertex attribute so that OpenGL knows how to read the VBO:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the vertex attribute so that OpenGL knows how to use it:
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which shader program we want to use:
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it:
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}