// TODO: ADD Delete function to LightCube class.
#ifndef LIGHTCUBE_CLASS_H
#define LIGHTCUBE_CLASS_H

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"

class LightCube
{
    public:
    glm::vec4 lightColor_ = glm::vec4(.80f, .20f, .20f, 0.8f);
    glm::vec3 lightPos_ = glm::vec3(0.0f, 5.0f, 0.0f);
    glm::mat4 lightModel_ = glm::mat4(1.0f);
    VAO lightVAO_;
    Shader* lightShaderptr_;

    LightCube(float scalingFactor) { Scale(scalingFactor); };

    void createLightCube();

    void renderLightCube(Camera& camera);

    void Scale(float scalingFactor);
};

#endif // LIGHTCUBE_CLASS_H