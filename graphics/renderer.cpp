#if _WIN32
#include <windows.h>
#endif

#include <filesystem>
#include "Mesh.h"


const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates.
Vertex vertices[] =
{           //  COORDINATES                /  COLORS                    /  TexCoord                  /  NORMALS            //
    Vertex{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
    Vertex{ glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
};

// Indices for vertices order to draw.
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{ // Coordinates
    Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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

    // Texture relative path.
    std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    std::string texPath = "/build/graphics/assets/";

    // Texture:
    Texture textures[] {
        Texture((parentDir + texPath + "spaceship_texture.jpg").c_str(),           "diffuse",  0, GL_RGB, GL_UNSIGNED_BYTE),
        Texture((parentDir + texPath + "spaceship_texture_spec.jpg").c_str(),  "specular", 1, GL_RGB, GL_UNSIGNED_BYTE)
    };

    // Generates Shader object using shaders default.vert and default.frag:
    Shader shaderProgram("graphics/shaders/default.vert", "graphics/shaders/default.frag");
    // Store mesh data in vectors for the mesh.
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    // Createfloor mesh:
    Mesh floor(verts, ind, tex);

    // Shader for light cube.
    Shader lightShader("graphics/shaders/light.vert", "graphics/shaders/light.frag");
    // Store mesh data in vectors for the mesh.
    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    // Create light mesh:
    Mesh light(lightVerts, lightInd, tex);


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Loop until the user closes the window:
    while(!glfwWindowShouldClose(window)) {
        // Render Here:
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color of the background.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and assign the new color to it.

        // Handles camera inputs:
        camera.Inputs(window);
        // Updates and exports the camera matrix to the vertex shader:
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draws different meshes:
        floor.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);

        // Sawp the back buffer with the front buffer:
        glfwSwapBuffers(window);

        // Poll for and process events(Refreshes the window basically):
        glfwPollEvents();
    }

    // Delete all the objects that were created:
    shaderProgram.Delete();
    lightShader.Delete();


    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();
    return 0;
}