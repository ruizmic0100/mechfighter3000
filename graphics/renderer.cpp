#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <filesystem>

#include "renderer.h"
#include "LightCube.h"
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerMechMenu.h"
#include "RenderList.h"
#include "Input.h"
#include "BattleMenu.h"

// TODO: Add render draw list. It should take care of what gets updated to our next frame.
// NOTE: Sorta adding here a render list but needs more work...
extern bool renderPlayerMechMenu=false, renderMainMenu=false, renderBattleMenu=false, renderLootMenu=false;

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
    std::string TestAreaPath = "/graphics/models/TestArea/scene.gltf";
    std::string devcubePath = "/graphics/models/devcube/scene.gltf";

    Model TestArea((parentDir + TestAreaPath).c_str());
    Model devcube((parentDir + devcubePath).c_str());

    model_list_temp.push_back(TestArea);
    model_list_temp.push_back(devcube);

    return model_list_temp;
}

// Simple helper function to load an image into a OpenGL texture with common settings.
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    // Flips the image so it appears right side up.
    stbi_set_flip_vertically_on_load(false);
    // Reads the image from a file and stores it in bytes.
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;
    
    // Create a OpenGL texture identifier.
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture.
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
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

    /* ------------------------ Init Sequence Finished ---------------------------*/
    Input auxInputs;

    // TODO: Load Fonts Section

    // Generates Shader object using shaders default.vert and default.frag:
    LightCube lightcubeinst_1(4);
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


    // Variables to create periodic events for FPS:
    double prevTime = 0.0f;
    double crntTime = 0.0f;
    double timeDiff;

    // Keeps track of the amount of frames in timeDiff
    unsigned int counter = 0;

    // Testing image textures for imgui
    std::string imagePath = parentDir + "/graphics/textures/Mech_Head_1.png";
    const char* image = imagePath.c_str();
    int my_image_width = 0;
    int my_image_height = 0;

    GLuint mechhead_texture = 0;

    bool ret = LoadTextureFromFile(image, &mechhead_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
    

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:

        // glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Updated counter and times.
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;

        if (timeDiff >= 1.0/30.0) {
            // Resets times and counter.
            prevTime = crntTime;
            counter = 0;
            camera.Inputs(window); // Handles camera inputs.
        }

        // Handles other player inputs that aren't movement/looking.
        auxInputs.Inputs(window);

        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 400.0f);

        // Draw all the models:
        for (std::vector<Model>::iterator it = model_list.begin(); it != model_list.end(); it++) {
            if (it == model_list.begin())
                it->Draw(shaderProgram, camera, glm::vec3(0.0f, 1.0f, -8.0f), glm::quat(cos(glm::radians(270.0f/2)), 0, sin(glm::radians(270.0f/2))*1, 0.0f));
            else
                it->Draw(shaderProgram, camera, glm::vec3(-3.0f, 1.0f, -10.0f));
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
        

        if (renderPlayerMechMenu) {
            Render(PlayerInstance, EnemyInstance, mechhead_texture);
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