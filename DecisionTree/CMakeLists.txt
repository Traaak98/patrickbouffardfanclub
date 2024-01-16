cmake_minimum_required(VERSION 3.5)
project(decision_tree)

set(CMAKE_BUILD_TYPE debug) # compilation en mode debug
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11") # options

file(
    GLOB_RECURSE
    source_files
    src/*
)

add_executable(${PROJECT_NAME} src/main.cpp)
