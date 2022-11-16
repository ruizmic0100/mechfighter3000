#if _WIN32
#include <windows.h>
#endif

#include <filesystem>
#include "Model.h"


const unsigned int width = 800;
const unsigned int height = 800;

// Takes care of the information needed to draw the windows.
const unsigned int numWindows = 100;
glm::vec3 positionsWin[numWindows];
float rotationsWin[numWindows];

// Takes care of drawing the windows in the right order.
unsigned int orderDraw[numWindows];
float distanceCamera[numWindows];

float rectangleVertices[] =
{
    // Coords       // texCoords
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f
};

// Compare function:
int compare(const void* a, const void* b)
{
    double diff = distanceCamera[*(int*)b] - distanceCamera[*(int*)a];
    return (0 < diff) - (diff < 0);
}

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
    Shader grassProgram("graphics/shaders/default.vert", "graphics/shaders/grass.frag");
    Shader winProgram("graphics/shaders/default.vert", "graphics/shaders/windows.frag");
    Shader framebufferProgram("graphics/shaders/framebuffer.vert", "graphics/shaders/framebuffer.frag");
    // Shader outliningProgram("graphics/shaders/outlining.vert", "graphics/shaders/outlining.frag");

    // Take care of all the light related things:
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    grassProgram.Activate();
    glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    framebufferProgram.Activate();
    glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);

    // Enables the depth buffer:
    glEnable(GL_DEPTH_TEST);
    // Enables Cull Facing:
    glEnable(GL_CULL_FACE);
    // Keeps front fraces.
    glCullFace(GL_FRONT);
    // Uses counter clock-wise standard.
    glFrontFace(GL_CCW);
    // Configures the blending function.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_STENCIL_TEST);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // glDepthFunc(GL_LESS);

    // Creates camera object.
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Relative path setup:
    std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    std::string groundPath = "/graphics/models/ground/scene.gltf";
    std::string modelPath = "/graphics/models/grindstone/scene.gltf";
    std::string grassPath = "/graphics/models/grass/scene.gltf";
    std::string winPath = "/graphics/models/windows/scene.gltf";

    // Load in models:
    Model model((parentDir + modelPath).c_str());
    Model ground((parentDir + groundPath).c_str());
    Model grass((parentDir + grassPath).c_str());
    Model windows((parentDir + winPath).c_str());

    unsigned int rectVAO, rectVBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    double prevTime = 0.0;
    double currTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;

    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer error: " << fboStatus << std::endl;

    // Generates all windows:
    for (unsigned int i = 0; i < numWindows; i++) {
        positionsWin[i] = glm::vec3 
        (
            -15.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (15.0f - (-15.0f)))),
            1.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (4.0f - 1.0f))),
            -15.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (15.0f - (-15.0f))))
        );
        rotationsWin[i] = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 1.0f));
        orderDraw[i] = i;
    }

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:

        // FPS counter logic:
        currTime = glfwGetTime();
        timeDiff = currTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "MechFighter3000 - " + FPS + "FPS / " + ms + "ms";
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = currTime;
            counter = 0;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.
        glEnable(GL_DEPTH_TEST);

        // Handles camera inputs:
        // NOTE: this might need to be placed in a time loop to make it not dependent on FPS.
        camera.Inputs(window);
        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 400.0f);

        // Draw a model:
        // glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // glStencilMask(0xFF);
        ground.Draw(shaderProgram, camera);
        model.Draw(shaderProgram, camera);

        // Disable cull face so that grass and windows have both faces:
        glDisable(GL_CULL_FACE);
        grass.Draw(grassProgram, camera);
        // Enable blending for windows.
        glEnable(GL_BLEND);
        // Get distance from each window to the camera:
        for (unsigned int i = 0; i < numWindows; i++) {
            distanceCamera[i] = glm::length(camera.Position - positionsWin[i]);
        }
        // Sort windows by distance from camera.
        qsort(orderDraw, numWindows, sizeof(unsigned int), compare);
        // Draw windows:
        for (unsigned int i = 0; i < numWindows; i++) {
            windows.Draw(winProgram, camera, positionsWin[orderDraw[i]], glm::quat(1.0f, 0.0f, rotationsWin[orderDraw[i]], 0.0f));
        }
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        framebufferProgram.Activate();
        glBindVertexArray(rectVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        

        // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        // glStencilMask(0x00);
        // glDisable(GL_DEPTH_TEST);
        // outliningProgram.Activate();
        // glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
        // model.Draw(outliningProgram, camera);

        // glStencilMask(0xFF);
        // glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    shaderProgram.Delete();
    grassProgram.Delete();
    winProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}