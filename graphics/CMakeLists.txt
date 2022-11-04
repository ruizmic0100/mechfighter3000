include_directories( ${OPENGL_INCLUDE_DIRS} glad/include/glad )

add_library( graphics renderer.cpp EBO.cpp EBO.h VAO.cpp VAO.h VBO.cpp VBO.h shaderClass.cpp shaderClass.h renderer.h)

target_include_directories( graphics PUBLIC ${OPENGL_INCLUDE_DIRS} glad/include/glad )
target_link_libraries( graphics ${OPENGL_LIBRARIES} glfw glad util game )