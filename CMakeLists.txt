cmake_minimum_required (VERSION 3.15)

project(Hydrogen)

SET(DATA_DIR "${CMAKE_CURRENT_LIST_DIR}/data")
SET(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/sdl")
SET(CGLM_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/cglm")
SET(LIBYAML_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/libyaml")

add_subdirectory(${LIBYAML_DIR})

# packages
find_package(SDL2 REQUIRED)
find_package(CGLM REQUIRED)
find_package(OpenGL REQUIRED)

# includes
include_directories(inc)
include_directories(${LIBYAML_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CGLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

# Exe
add_executable(
  Main
  src/main.c
  src/world.c
  src/game_object.c
  src/camera.c
  src/recycled_index.c
  src/systems_camera.c)

# Ext linking
target_link_libraries(Main ${SDL2_LIBRARIES})
target_link_libraries(Main ${CGLM_LIBRARIES})
target_link_libraries(Main ${OPENGL_LIBRARIES})
add_dependencies(Main yaml)

# Post
file(COPY ${SDL2_DIR}/lib/x64/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${DATA_DIR}/object.yaml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
