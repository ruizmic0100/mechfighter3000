add_library( util logging.cpp Maths.cpp NameGenerator.cpp )
include_directories( ${PROJECT_SOURCE_DIR}/util )
target_include_directories( util PUBLIC ${PROJECT_SOURCE_DIR}/util )