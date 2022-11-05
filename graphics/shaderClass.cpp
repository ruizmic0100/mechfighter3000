#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::cout << "Current Working Directory: " << std::filesystem::current_path().string() << std::endl;
    std::ifstream in(filename, std::ios::binary);

    if (in) {
        std::cout << "\nGetting '" << filename << "' Contents..." << std::endl;
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    std::cout << "\nCouldn't Getting File Contents" << std::endl;
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Read vertexFile and fragmentFile and store the strings:
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays:
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get reference:
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source to the vertex shader object:
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the vertex shader into machine code:
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get reference:
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source to the fragment shader object:
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the fragment shader into machine code:
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    // Create shader program object and get it's reference:
    ID = glCreateProgram();
    // Attach the vertex and fragment shaders to the shader program:
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/link all the shaders together into the shader program:
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    // Delete the now useless shaders:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Activates the shader program.
void Shader::Activate()
{
    glUseProgram(ID);
}

// Deletes the shader program.
void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
    // Stores status fo compilation.
    GLint hasCompiled;

    // Character array to store error message in.
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}