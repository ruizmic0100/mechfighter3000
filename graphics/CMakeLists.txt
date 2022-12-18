add_subdirectory( menu )

add_library( graphics Renderer.cpp EBO.cpp EBO.h VAO.cpp VAO.h VBO.cpp VBO.h shaderClass.cpp stb.cpp Texture.cpp Camera.cpp Mesh.cpp Model.cpp LightCube.cpp MechMenu.cpp EnemyMenu.cpp PopUpMenu.cpp Menu/imguipp.cpp Animation.cpp )
target_include_directories( graphics PUBLIC ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad ${PROJECT_SOURCE_DIR}/stb ${PROJECT_SOURCE_DIR}/glm ${PROJECT_SOURCE_DIR}/imgui ${PROJECT_SOURCE_DIR}/graphics/menu )
target_link_libraries( graphics ${OPENGL_LIBRARIES} glfw glad util game IMGUI)