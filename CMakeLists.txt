cmake_minimum_required(VERSION 3.26)
project(raytracing_test CXX)

set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/lib src/helpers)

add_executable(raytracing_test
        src/main.cpp
        src/lib/hittables/sphere.cpp)

