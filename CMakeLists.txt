cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(high-performance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} "./high-performace.cpp")