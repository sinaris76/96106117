cmake_minimum_required(VERSION 3.9)
project(project C)

set(CMAKE_C_STANDARD 99)

add_executable(pacman main.c src/physics.c src/game.c)

INCLUDE_DIRECTORIES(/usr/include/SDL2)

ADD_DEFINITIONS(-D_REENTRANT)

TARGET_LINK_LIBRARIES(pacman m SDL2 SDL2_gfx)
