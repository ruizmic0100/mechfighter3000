#include "Animation.h"

void translateModelOverADistance(Shader& shader, Camera& camera, glm::vec3* startLocation, glm::vec3 endLocation)
{
    float x=0.0f, y=0.0f, z=0.0f;
    float interpolationFactor = 0.1f;

    if (startLocation->x >= endLocation.x) { startLocation->x = 0.0f; }

    startLocation->x += interpolationFactor;
}