cmake_minimum_required(VERSION 3.0.0...3.24 FATAL_ERROR)
project(DAWN_LIB VERSION 1.0.0)

message(STATUS "Using Dawn backend for WebGPU")

include(dawn.cmake)

add_library(DAWN_LIB STATIC src/Empty.cpp)

target_link_libraries(DAWN_LIB PUBLIC webgpu_dawn webgpu_cpp)
