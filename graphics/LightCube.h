// TODO: ADD Delete function to LightCube class.
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"

class LightCube
{
    public:
    glm::vec4 lightColor_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos_ = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel_ = glm::mat4(1.0f);
    VAO lightVAO_;
    Shader* lightShaderptr_;

    LightCube(float scalingFactor) { Scale(scalingFactor); };

    void createLightCube();

    void renderLightCube(Camera& camera);

    void Scale(float scalingFactor);
};