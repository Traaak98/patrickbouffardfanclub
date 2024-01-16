cmake_minimum_required(VERSION 3.5)
project(cnn)

set(CMAKE_BUILD_TYPE debug) # compilation en mode debug
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11") # options

file(# liste des fichiers à compiler
    GLOB_RECURSE # recherche récursive
    source_files # fichiers listés dans une variable source_files
    src/*.cpp # forme des fichiers à rechercher
)

add_executable(${PROJECT_NAME} ${source_files})
