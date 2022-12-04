add_library( menu imguipp.cpp )
target_include_directories( menu PUBLIC ${OPENGL_INLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad ${PROJECT_INCLUDE_DIR}/glm ${PROEJCT_INCLUDE_DIR}/imgui )
target_link_libraries( menu ${OPENGL_LIBRARIES} glfw gla util game IMGUI)