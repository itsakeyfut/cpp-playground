cmake_minimum_required(VERSION 3.20)
project(if_init CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_executable(example example.cpp)
add_executable(exercise exercise.cpp)
add_executable(solution solution.cpp)
