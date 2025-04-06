cmake_minimum_required(VERSION 4.0)
project(ReindeerMaze VERSION 1.0)
set(SOURCES
    src/maze.cpp
    src/main.cpp
)

add_executable(ReindeerMaze ${SOURCES})
target_include_directories(ReindeerMaze PRIVATE include)

add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )
