cmake_minimum_required(VERSION 3.17)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp vec3.hpp ray.hpp)