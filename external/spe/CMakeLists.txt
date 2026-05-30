cmake_minimum_required(VERSION 3.27.3)

project(SPE)

set(SOURCE_FILES
    src/Particle.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC include)