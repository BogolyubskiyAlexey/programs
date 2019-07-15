cmake_minimum_required(VERSION 2.6)

project(GameLifeLibrary)
set(SOURCES game.cpp)
set(HEADERS game.h)
add_library(game_lib ${SOURCES} ${HEADERS})
target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
