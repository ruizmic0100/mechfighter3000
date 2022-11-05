include_directories( ${OPENGL_INCLUDE_DIRS} glad/include/glad ${PROJECT_SOURCE_DIR}/stb)

add_library( graphics renderer.cpp EBO.cpp EBO.h VAO.cpp VAO.h VBO.cpp VBO.h shaderClass.cpp shaderClass.h renderer.h stb.cpp Texture.cpp)

target_include_directories( graphics PUBLIC ${OPENGL_INCLUDE_DIRS} glad/include/glad ${PROJECT_SOURCE_DIR}/stb)
target_link_libraries( graphics ${OPENGL_LIBRARIES} glfw glad util game)