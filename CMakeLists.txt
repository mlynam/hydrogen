cmake_minimum_required (VERSION 3.15)

project(Hydrogen)

SET(DATA_DIR "${CMAKE_CURRENT_LIST_DIR}/data")
SET(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/sdl")
SET(CGLM_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/cglm")
SET(LIBYAML_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/libyaml")
SET(CHECK_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/check")

SET(CHECK_INSTALL_DIR "C:/Program Files (x86)/Hydrogen")

add_subdirectory(${LIBYAML_DIR})
add_subdirectory(${CHECK_DIR})

# packages
find_package(SDL2 REQUIRED)
find_package(CGLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Check REQUIRED)

# includes
include_directories(inc)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CHECK_INSTALL_DIR}/include)
include_directories(${CGLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

add_library(
  Library
  src/world.c
  src/game_object.c
  src/camera.c
  src/recycled_index.c
  src/systems_camera.c
)

# Exe
add_executable(
  Main
  src/main.c
  src/world.c
  src/game_object.c
  src/camera.c
  src/recycled_index.c
  src/systems_camera.c)

add_executable(
  Test
  test/runner.c)

# Ext linking
target_link_libraries(Main ${SDL2_LIBRARIES})
target_link_libraries(Main ${CGLM_LIBRARIES})
target_link_libraries(Main ${OPENGL_LIBRARIES})
target_link_libraries(Main yaml)
target_link_libraries(Library ${SDL2_LIBRARIES})
target_link_libraries(Library ${CGLM_LIBRARIES})
target_link_libraries(Library ${OPENGL_LIBRARIES})
target_link_libraries(Library yaml)
target_link_libraries(Test yaml)
target_link_libraries(Test ${SDL2_LIBRARIES})
target_link_libraries(Test check)
target_link_libraries(Test Library)

add_dependencies(Main yaml)
add_dependencies(Test check)
add_dependencies(Library yaml)

# Post
# file(COPY ${SDL2_DIR}/lib/x64/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/<$Configuration>)
# file(COPY ${DATA_DIR}/object.yaml DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/<$Configuration>)
