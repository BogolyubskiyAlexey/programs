cmake_minimum_required(VERSION 2.6)

project(ConsoleLibrary)
set(SOURCES console.cpp)
set(HEADERS console.h)
add_library(console ${SOURCES} ${HEADERS})
target_include_directories(console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
