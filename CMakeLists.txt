cmake_minimum_required( VERSION 3.1 )

project( mechfighter3000 )

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )

add_subdirectory( glfw )
add_subdirectory( core )
