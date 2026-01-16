cmake_minimum_required(VERSION 3.20)
project(cpp17_exercises CXX)

# C++17を要求
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 警告レベルの設定
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 各演習をサブディレクトリとして追加
message(STATUS "Building C++17 exercises...")

add_subdirectory(exercises/01-structured-bindings)
add_subdirectory(exercises/02-if-init)
add_subdirectory(exercises/03-ctad)
add_subdirectory(exercises/04-constexpr-if)
add_subdirectory(exercises/05-fold-expressions)
add_subdirectory(exercises/06-attributes)
add_subdirectory(exercises/07-optional)
add_subdirectory(exercises/08-variant)
add_subdirectory(exercises/09-string-view)
add_subdirectory(exercises/10-filesystem)

message(STATUS "C++17 exercises configured successfully!")
