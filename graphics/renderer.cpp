#if _WIN32
#include <windows.h>
#endif

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <filesystem>
#include "math.h"
#include "Model.h"
#include "LightCube.h"

#include "../game/Mech_Factory.h"


// TODO: ADD inputhandler for both imgui and my application. https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-how-can-i-tell-whether-to-dispatch-mousekeyboard-to-dear-imgui-or-my-application:~:text=Q%3A%20How%20can%20I%20tell%20whether%20to%20dispatch%20mouse/keyboard%20to%20Dear%20ImGui%20or%20my%20application%3F
// TODO: Add render dispatcher. It should take care of what gets updated to our next frame.

// Screen dimensions.
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

// TODO: Add compare and randf functions to utils/math file.
// Compare function:
int compare(const void* a, const void* b)
{
    double diff = distanceCamera[*(int*)b] - distanceCamera[*(int*)a];
    return (0 < diff) - (diff < 0);
}

float randf()
{
    return -1.0f + (rand() / (RAND_MAX / 2.0f));
}

/**
 * @brief Steps taken to render the window.
 * 
 * @return
 */
int renderer()
{
    const char* glsl_version = "#version 130";

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

    // Setup Dear ImGui context:
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    
    // Setup Dear ImGui Style:
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends:
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // TODO: Load Fonts Section


    // Generates Shader object using shaders default.vert and default.frag:
    LightCube lightcubeinst_1(10);
    lightcubeinst_1.createLightCube();
    Shader shaderProgram("graphics/shaders/default.vert", "graphics/shaders/default.frag");
    Shader grassProgram("graphics/shaders/default.vert", "graphics/shaders/grass.frag");
    // Shader framebufferProgram("graphics/shaders/framebuffer.vert", "graphics/shaders/framebuffer.frag");

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
    grassProgram.Activate();
    glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
    // framebufferProgram.Activate();
    // glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);

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

    // Creates camera object.
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Relative path setup:
    std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    std::string groundPath = "/graphics/models/ground/scene.gltf";
    std::string grassPath = "/graphics/models/grass/scene.gltf";

    // Load in models:
    Model ground((parentDir + groundPath).c_str());
    Model grass((parentDir + grassPath).c_str());

    // Creating framebuffer's post processing affects and adding them to their corresponding buffers.
    // unsigned int rectVAO, rectVBO;
    // glGenVertexArrays(1, &rectVAO);
    // glGenBuffers(1, &rectVBO);
    // glBindVertexArray(rectVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // unsigned int FBO;
    // glGenFramebuffers(1, &FBO);
    // glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // unsigned int framebufferTexture;
    // glGenTextures(1, &framebufferTexture);
    // glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    // unsigned int RBO;
    // glGenRenderbuffers(1, &RBO);
    // glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    // auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    // if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
    //     std::cout << "Framebuffer error: " << fboStatus << std::endl;

    
    // FPS/ms title counter logic:
    double prevTime = 0.0;
    double currTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;

    // Our ImGui State.
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Dev Frame init
    Frame dev_frame = dev_mech_frame_init();


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

        // glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Handles camera inputs:
        // NOTE: this might need to be placed in a time loop to make it not dependent on FPS.
        camera.Inputs(window);
        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 400.0f);

        // Draw a model:
        // glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // glStencilMask(0xFF);
        ground.Draw(shaderProgram, camera);

        // Disable cull face so that grass and windows have both faces:
        glDisable(GL_CULL_FACE);
        grass.Draw(grassProgram, camera);

        // Framebuffer postprocessing logic.
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // framebufferProgram.Activate();
        // glBindVertexArray(rectVAO);
        // glDisable(GL_DEPTH_TEST);
        // glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        

        // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        // glStencilMask(0x00);
        // glDisable(GL_DEPTH_TEST);
        // outliningProgram.Activate();
        // glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
        // model.Draw(outliningProgram, camera);

        // glStencilMask(0xFF);
        // glStencilFunc(GL_ALWAYS, 0, 0xFF);

        // Render light cube:
        lightcubeinst_1.renderLightCube(camera);

        // Used to capture mouse/keyboard inputs for ImGui and not dispatch input data to main application.
        io.WantCaptureMouse = true;

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();


        // Start the Dear ImGui Frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show a simple window. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Mech Data"); // Create a window called "Hello, World" and append into it.
            
            ImGui::Text("Dev Mech"); // Display some text (you can use a format strings too).
            ImGui::Checkbox("Mech Data Window", &show_demo_window); // Edit bools storing our window open/close state.
            ImGui::Checkbox("Inventory", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f.
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color.

            if (ImGui::Button("Increase Stat"))        // Buttons return true when clicked (most widgets return true when editted/activated).
                counter++;
            
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Name: %s", dev_frame.Name_.c_str());
            ImGui::Text("Manufacturer: %s", dev_frame.Manufacturer_.c_str());
            ImGui::Text("Identifier: %s", dev_frame.Identifier_.c_str());
            ImGui::Text("Price: %d", dev_frame.Price_);
            ImGui::Text("Name: %d", dev_frame.Weight_);
            ImGui::Text("Ballistic Defense: %i", dev_frame.Defenses_.ballisticDefense);
            ImGui::Text("Energy Defense: %i", dev_frame.Defenses_.energyDefense);
            ImGui::End();
        }

        if (show_another_window) {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me!"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);
    }

    // Delete all the objects that were created:
    shaderProgram.Delete();
    grassProgram.Delete();
    // TODO: Call LightCube.Delete() here.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}