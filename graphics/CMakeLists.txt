include_directories( ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad ${PROJECT_SOURCE_DIR}/stb ${PROJECT_SOURCE_DIR}/glm ${PROJECT_SOURCE_DIR}/glfw ${PROJECT_SOURCE_DIR}/imgui ${PROJECT_SOURCE_DIR}/game)

add_library( graphics renderer.cpp EBO.cpp EBO.h VAO.cpp VAO.h VBO.cpp VBO.h shaderClass.cpp shaderClass.h renderer.h stb.cpp Texture.cpp Camera.cpp Mesh.cpp Model.cpp LightCube.cpp)

target_include_directories( graphics PUBLIC ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad ${PROJECT_SOURCE_DIR}/stb ${PROJECT_SOURCE_DIR}/glm ${PROJECT_SOURCE_DIR}/imgui)
target_link_libraries( graphics ${OPENGL_LIBRARIES} glfw glad util game IMGUI)