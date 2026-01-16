cmake_minimum_required(VERSION 3.20)
project(modules CXX)

# C++20を要求
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 警告レベルの設定
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 注意: モジュールは実験的機能のため、標準的なヘッダーベースの実装を使用
# 実際のモジュールを使うには追加の設定が必要

# 実行ファイルの作成
add_executable(example example.cpp)
add_executable(exercise exercise.cpp)
add_executable(solution solution.cpp)
