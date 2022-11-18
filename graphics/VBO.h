#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "../glm/glm.hpp"
#include <glad/glad.h>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO
{

    public:
        // Reference ID of the vertex buffer object.
        GLuint ID;
        // Contructor that gerneates a Vertex Buffer Object and links it to vertices.
        VBO(GLfloat* vertices, GLsizeiptr size);
        VBO(std::vector<Vertex>& vertices);
        VBO(std::vector<glm::mat4>& mat4s);

        void Bind();
        void Unbind();
        void Delete();
};



#endif // VBO_CLASS_H