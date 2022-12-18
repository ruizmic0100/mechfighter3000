#include "Animation.h"

void translateModelOverADistance(Shader& shader, Camera& camera, Model& model, glm::vec3 endLocation)
{
    float x=0.0f, y=0.0f, z=0.0f;
    // std::vector<glm::vec3>& translationMeshes = model.GetTranslationMeshes();
    std::vector<Mesh> meshData = model.GetMeshes();


    while (x != endLocation.x && y != endLocation.y && z != endLocation.z) {
        x++; y++; z++;
    }
}