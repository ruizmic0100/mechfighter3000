#include "LightCube.h" 
 
 GLfloat lightVertices[] =
{
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
    0.1f,  0.1f, -0.1f,
    0.1f,  0.1f,  0.1f
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

void LightCube::Scale(float scalingFactor)
{
    size_t lightVerticesSize = sizeof(lightVertices) / sizeof(lightVertices[0]);
    for (unsigned int i = 0; i < lightVerticesSize; i++) {
        lightVertices[i] = lightVertices[i] * scalingFactor;
    }
}

void LightCube::createLightCube()
{
    LightCube::lightShaderptr_ = new Shader("graphics/shaders/light.vert", "graphics/shaders/light.frag");
    // Generates the Vertex Array Object and binds it.
    // VAO lightVAO;
    LightCube::lightVAO_.Bind();

    // Generates Vertex Buffer Object and links it to vertices.
    VBO lightVBO(lightVertices, sizeof(lightVertices));

    // Generates Element Buffer Object and links it to indices.
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    // Links VBO attributes such as coordinates and colors to VAO.
    LightCube::lightVAO_.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind all to prevent accidentally modifying them.
    LightCube::lightVAO_.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    // Positons the cube.
    LightCube::lightModel_ = glm::translate(LightCube::lightModel_, LightCube::lightPos_);

    // Activates the light shader with the input color.
    LightCube::lightShaderptr_->Activate();
    glUniformMatrix4fv(glGetUniformLocation(LightCube::lightShaderptr_->ID, "model"), 1, GL_FALSE, glm::value_ptr(LightCube::lightModel_));
    glUniform4f(glGetUniformLocation(LightCube::lightShaderptr_->ID, "lightColor"), LightCube::lightColor_.x, LightCube::lightColor_.y, LightCube::lightColor_.z, LightCube::lightColor_.w);
}

void LightCube::renderLightCube(Camera& camera)
{
    LightCube::lightShaderptr_->Activate();
    camera.Matrix(*LightCube::lightShaderptr_, "camMatrix");
    LightCube::lightVAO_.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

// TODO: This should probably call a rebake pipeline.
void LightCube::SetLightColor(glm::vec4 lightColor)
{
    this->lightColor_ = lightColor;
    LightCube::lightShaderptr_->Activate();
    glUniform4f(glGetUniformLocation(LightCube::lightShaderptr_->ID, "lightColor"), LightCube::lightColor_.x, LightCube::lightColor_.y, LightCube::lightColor_.z, LightCube::lightColor_.w);
}