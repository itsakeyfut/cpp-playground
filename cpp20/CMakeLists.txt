cmake_minimum_required(VERSION 3.20)
project(cpp20_exercises CXX)

# C++20を要求（Unreal Engine 5.7の最小要件）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 警告レベルの設定
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 各演習をサブディレクトリとして追加
message(STATUS "Building C++20 exercises (Unreal Engine 5.7 compatible)...")

add_subdirectory(exercises/01-concepts)
add_subdirectory(exercises/02-ranges)
add_subdirectory(exercises/03-coroutines)
add_subdirectory(exercises/04-modules)
add_subdirectory(exercises/05-span)
add_subdirectory(exercises/06-format)
add_subdirectory(exercises/07-three-way-comparison)
add_subdirectory(exercises/08-constexpr-extensions)
add_subdirectory(exercises/09-designated-initializers)

message(STATUS "C++20 exercises configured successfully!")
message(STATUS "Priority exercises for UE 5.7: Concepts, Ranges, span")
