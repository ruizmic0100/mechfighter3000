#if _WIN32
#include <windows.h>
#endif

#include <filesystem>
#include "Model.h"


const unsigned int width = 800;
const unsigned int height = 800;

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

    // Take care of all the light related things:
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enables the depth buffer:
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Relative path setup:
    std::string parentModelDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    std::string modelPath = "/graphics/models/grindstone/scene.gltf";

    // Load in a model:
    Model model((parentModelDir + modelPath).c_str());

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Handles camera inputs:
        camera.Inputs(window);
        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 400.0f);

        // Draw a model:
        model.Draw(shaderProgram, camera);

        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}