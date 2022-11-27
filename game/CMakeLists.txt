add_library( game GameEventHandler.cpp Player.cpp Mech_Factory.cpp PartsFactory.cpp Inventory.cpp Enemy.cpp )
target_link_libraries( game ${OPENGL_LIBRARIES} glfw glad util IMGUI graphics)
