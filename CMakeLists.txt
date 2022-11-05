cmake_minimum_required( VERSION 3.1 )

project( mechfighter3000 )

find_package( OpenGL REQUIRED )
set( CMAKE_CXX_STANDARD 17 )


if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )

add_subdirectory( glfw )
add_subdirectory( glad )
add_subdirectory( game )
add_subdirectory( graphics )
add_subdirectory( util )

set( GLFW-CMAKE-MECHFIGHTER-SRC ./game/MechFighter.cpp )

# add_executable(MechFighter3000 WIN32 ${GLFW-CMAKE-MECHFIGHTER-SRC} ./game/graphics/renderer.cpp ./game/util/logging.cpp ./glad/src/glad.c)
add_executable( MechFighter3000 WIN32 ${GLFW-CMAKE-MECHFIGHTER-SRC} )

add_custom_target(copy_resources ALL
        COMMENT "Copying shaders into binary directory..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/graphics/shaders
        ${PROJECT_BINARY_DIR}/graphics/shaders
        COMMENT "Copying assets into binary directory..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/graphics/assets/
        ${PROJECT_BINARY_DIR}/graphics/assets/
)

add_dependencies(MechFighter3000 copy_resources)

target_include_directories( MechFighter3000 PUBLIC ${OPENGL_INCLUDE_DIRS} glad/include/glad glm)
target_link_libraries( MechFighter3000 ${OPENGL_LIBRARIES} glfw glad graphics util game)

if( MSVC )
    if( ${CMAKE_VERSION} VERSION_LESS "3.6.0" )
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMAKE and rerun; OR\n\t - Manually set 'GLFW-CMAKE-starter' as StartUp Project in Visual Studio.\n" )
    else()
        message( "\n\t[ SET PROPERTY ] MechFighter3000 as vs startup project.\n" )
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MechFighter3000 )
    endif()
endif()