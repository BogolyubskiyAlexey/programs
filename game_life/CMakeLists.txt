cmake_minimum_required(VERSION 2.6)

project(game_life)

add_executable(game_life main.cpp)

add_subdirectory(console)
target_link_libraries(game_life console)

add_subdirectory(game)
target_link_libraries(game_life game_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

