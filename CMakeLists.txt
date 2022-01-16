cmake_minimum_required(VERSION 3.21)
project(connect_four C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2 -pthread")

find_package(SDL2 REQUIRED)

include_directories(Basecode)

add_executable(connect_four
        Basecode/IA.c
        Basecode/IA.h
        Basecode/Jeu.c
        Basecode/Jeu.h
        Basecode/main.c
        Basecode/TestJeu.c
        Basecode/TestJeu.h
        Basecode/Sound.c
        Basecode/Sound.h)

target_link_libraries(connect_four SDL2::SDL2)
