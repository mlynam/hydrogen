cmake_minimum_required (VERSION 3.15)

project(Hydrogen)

SET(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/ext/sdl")

# SDL
find_package(SDL2 REQUIRED)

# includes
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Main src/main.c)
target_link_libraries(Main ${SDL2_LIBRARIES})
