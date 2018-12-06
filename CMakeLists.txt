cmake_minimum_required(VERSION 3.12)
project(Diabetes_Detection)

set(CMAKE_CXX_STANDARD 14)

add_executable(Diabetes_Detection main.cpp diabetes.cpp diabetes.h)

find_package(SDL2 REQUIRED COMPONENTS SDL2::SDL2)

include_directories(
        "${PROJECT_SOURCE_DIR}/INCLUDE"
        ${SDL2_INCLUDE_DIRS}
)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

target_link_libraries(Diabetes_Detection ${SDL2_LIBRARIES})