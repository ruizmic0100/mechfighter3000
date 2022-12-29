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

#include "Renderer.h"
#include "../game/Mech_Factory.h"
#include "../game/Player.h"
#include "MechMenu.h"
#include "EnemyMenu.h"
#include "../game/Enemy.h"
#include "Animation.h"



// TODO: Add render draw list. It should take care of what gets updated to our next frame.

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

// Relative Path for parent DIR.
std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

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

// TODO: Finish this. It's suppose to generate the shader program objects and generate a list of them.
//       The list will hopefully go into the render pipeline where a system of callbacks/signals will
//       cause the baking process to re-run if any changes are necessary. (Real-time lighting part 1 ig).
/** @brief Shader Program Generation.
 * 1. We create a Shader Program Object by passing in a vertex & frag shader.
 * 2. 
*/
void GenerateShaderProgramObjects()
{
    LightCube lightcubeinst_1(10);
    lightcubeinst_1.createLightCube();
    Shader shaderProgram("graphics/shaders/default.vert", "graphics/shaders/default.frag");
    Shader grassProgram("graphics/shaders/default.vert", "graphics/shaders/grass.frag");

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
    grassProgram.Activate();
    glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
}



/** @brief Model Loading
        1. .gltf standard makes use of the json file structure to organize the model data. Create a path to the scene.gltf.
        2. Create the model object.
        3. Draw the model object.

    TODO: this list is getting copied might want to fix this to either be created on the heap.
    TODO: grass needs to be rendered seperately so that culling can be used correctly.
*/
std::vector<Model> LoadModels()
{
    std::vector<Model> model_list_temp;

    // Relative path setup for each model specifically
    std::string groundPath = "/graphics/models/ground/scene.gltf";
    std::string grassPath = "/graphics/models/grass/scene.gltf";
    std::string testModelPath = "/graphics/models/testmodel/scene.gltf";
    std::string TestAreaPath = "/graphics/models/TestArea/scene.gltf";

    // Model ground((parentDir + groundPath).c_str());
    // Model grass((parentDir + grassPath).c_str());
    // Model testModel((parentDir + testModelPath).c_str());
    Model TestArea((parentDir + TestAreaPath).c_str());

    // model_list_temp.push_back(ground);
    // model_list_temp.push_back(grass);
    // model_list_temp.push_back(testModel);
    model_list_temp.push_back(TestArea);

    return model_list_temp;
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
    
    // Setup Platform/Renderer backends:
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // TODO: Load Fonts Section

    // Generates Shader object using shaders default.vert and default.frag:
    LightCube lightcubeinst_1(10);
    lightcubeinst_1.createLightCube();
    Shader shaderProgram("graphics/shaders/default.vert", "graphics/shaders/default.frag");
    Shader grassProgram("graphics/shaders/default.vert", "graphics/shaders/grass.frag");

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
    grassProgram.Activate();
    glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
    glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);

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
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));

    std::vector<Model> model_list = LoadModels();

    // TODO: Make this not be intialized here.
    Player PlayerInstance = PlayerInit();
    Enemy EnemyInstance = EnemyInit(RUST_CRAB);

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:

        // glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Handles camera inputs:
        // NOTE: this might need to be placed in a time loop to make it not dependent on FPS.
        // RenderHandler will choose here what to render...
        // For now just using simple keybinds on camera input.
       camera.Inputs(window);
        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 400.0f);

        // Draw all the models:
        for (std::vector<Model>::iterator it = model_list.begin(); it != model_list.end(); it++) {
            if (it == model_list.begin())
                it->Draw(shaderProgram, camera, glm::vec3(0.0f, 1.5f, -8.0f), glm::quat(cos(glm::radians(270.0f/2)), 0, sin(glm::radians(270.0f/2))*1, 0.0f));
            else
                it->Draw(shaderProgram, camera);
        }

        // Disable cull face so that grass and windows have both faces:
        // glDisable(GL_CULL_FACE);
        // grass.Draw(grassProgram, camera);

        // Render light cube:
        if (ChangeLightColor == true) {
            std::cout << "Changing Light Color: " << std::endl;
            lightcubeinst_1.SetLightColor(glm::vec4(getRandFloat(), getRandFloat(), getRandFloat(), getRandFloat()));
            std::cout << lightcubeinst_1.lightColor_.x << std::endl;
            // lightcubeinst_1.lightPos_ = glm::vec3(0.0f, 1.0f, 0.0f);
            shaderProgram.Activate();
            glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z, lightcubeinst_1.lightColor_.w);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightcubeinst_1.lightColor_.x, lightcubeinst_1.lightColor_.y, lightcubeinst_1.lightColor_.z);
            ChangeLightColor = !ChangeLightColor;
        }
        lightcubeinst_1.renderLightCube(camera);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
        
        if (showMechMenu) {
            MechMenu::Render(PlayerInstance, EnemyInstance);
        }


        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);
    }

    // Delete all the objects that were created:
    shaderProgram.Delete();
    grassProgram.Delete();
    // TODO: Call LightCube.Delete() here.

    // Shuts down imgui.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}