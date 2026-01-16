cmake_minimum_required(VERSION 3.20)
project(structured_bindings CXX)

# C++17を要求
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 警告レベルの設定
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 実行ファイルの作成
add_executable(example example.cpp)
add_executable(exercise exercise.cpp)
add_executable(solution solution.cpp)
