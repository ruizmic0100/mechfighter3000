#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{

    public:
        // ID reference of Elements Buffer Object.
        GLuint ID;
        // Constructor that generates an Elements BUffer Object and links it to the indices.
        EBO(std::vector<GLuint>& indices);

        // Binds the EBO.
        void Bind();
        // Unbinds the EBO
        void Unbind();
        // Deletes the EBO
        void Delete();
};

#endif // EBO_CLASS_H