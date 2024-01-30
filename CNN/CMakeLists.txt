cmake_minimum_required(VERSION 3.16)
project(cnn)

set(CMAKE_BUILD_TYPE debug) # compilation en mode debug
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11") # options
set(CMAKE_CXX_STANDARD 14)

file(# liste des fichiers à compiler
    GLOB_RECURSE # recherche récursive
    source_files # fichiers listés dans une variable source_files
    src/*.cpp # forme des fichiers à rechercher
)

include_directories(data model)

add_subdirectory(
    "/home/clara/tensorflow_src/tensorflow/lite"
    "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite" EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} tensorflow-lite)
