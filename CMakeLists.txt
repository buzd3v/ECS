cmake_minimum_required(VERSION 3.0.0)

project(ECS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ecs src/ecs.cpp)
