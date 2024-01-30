cmake_minimum_required(VERSION 3.16)
project(comparaison)

set(CMAKE_BUILD_TYPE debug) # compilation en mode debug
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11") # options
set(CMAKE_CXX_STANDARD 14)

file(# liste des fichiers à compiler
    GLOB_RECURSE # recherche récursive
    source_files # fichiers listés dans une variable source_files
    src/*.cpp # forme des fichiers à rechercher
)

include_directories(../../CNN/model ../../RandomForest ../../DecisionTree/src ../../SVM)

add_subdirectory(
    "/media/apolline/B2C2CC8EC2CC586D/apolline/Ecole/ENSTA/M2/tensorflow/tensorflow_src/tensorflow/lite"
    "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite" EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} tensorflow-lite)
