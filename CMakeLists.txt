cmake_minimum_required(VERSION 3.20...4.0)
project(cpp-playground
    VERSION 1.0.0
    DESCRIPTION "Modern C++ Learning Playground"
    LANGUAGES CXX
)

# Default to Release build if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Global compile options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard - Using C++20 for Unreal Engine 5.7 compatibility
# UE 5.7 requires C++20 as minimum version
# Can be overridden by individual targets if needed (e.g., C++23 for learning)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------------------------------------------
# Clang-Tidy integration
# -----------------------------------------------------------------------------
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

# -----------------------------------------------------------------------------
# Compiler warnings - Strict mode for safety
# -----------------------------------------------------------------------------
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

if(MSVC)
    # MSVC warnings
    add_compile_options(
        /W4              # High warning level
        /permissive-     # Standards conformance
        /w14242          # Conversion warnings
        /w14254          # Operator ambiguity
        /w14263          # Member function does not override
        /w14265          # Class has virtual functions but destructor is not virtual
        /w14287          # Unsigned/negative constant mismatch
        /w14296          # Expression is always true/false
        /w14311          # Pointer truncation
        /w14545          # Expression before comma has no effect
        /w14546          # Function call before comma missing argument list
        /w14547          # Operator before comma has no effect
        /w14549          # Operator before comma has no effect
        /w14555          # Expression has no effect
        /w14619          # Pragma warning suppression
        /w14640          # Thread-unsafe static member initialization
        /w14826          # Conversion is sign-extended
        /w14905          # Wide string literal cast
        /w14906          # String literal cast
        /w14928          # Illegal copy-initialization
    )
    if(ENABLE_WARNINGS_AS_ERRORS)
        add_compile_options(/WX)
    endif()
else()
    # GCC/Clang warnings
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wformat=2
        -Wnull-dereference
        -Wdouble-promotion
    )

    # Additional GCC-specific warnings
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
        )
    endif()

    if(ENABLE_WARNINGS_AS_ERRORS)
        add_compile_options(-Werror)
    endif()
endif()

# Enable colors in ninja
if(CMAKE_GENERATOR STREQUAL "Ninja")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-fdiagnostics-color=always)
    endif()
endif()

# -----------------------------------------------------------------------------
# Sanitizers (Debug builds only)
# -----------------------------------------------------------------------------
option(ENABLE_SANITIZERS "Enable sanitizers (AddressSanitizer, UndefinedBehaviorSanitizer)" OFF)

if(ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Enabling sanitizers: AddressSanitizer, UndefinedBehaviorSanitizer")
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address,undefined)
    else()
        message(WARNING "Sanitizers are only supported with GCC/Clang")
    endif()
endif()

# -----------------------------------------------------------------------------
# Options to control which parts to build
# -----------------------------------------------------------------------------
option(BUILD_CPP17 "Build C++17 exercises and projects" ON)
option(BUILD_CPP20 "Build C++20 exercises and projects" ON)
option(BUILD_CPP23 "Build C++23 exercises and projects" OFF)  # Requires newer compiler
option(BUILD_CPP26 "Build C++26 experiments" OFF)             # Experimental
option(BUILD_CROSS_CUTTING "Build cross-cutting topics" ON)
option(BUILD_SANDBOX "Build sandbox" ON)

# -----------------------------------------------------------------------------
# Subdirectories
# -----------------------------------------------------------------------------
if(BUILD_CPP17 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cpp17/CMakeLists.txt")
    add_subdirectory(cpp17)
endif()

if(BUILD_CPP20 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cpp20/CMakeLists.txt")
    add_subdirectory(cpp20)
endif()

if(BUILD_CPP23 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cpp23/CMakeLists.txt")
    add_subdirectory(cpp23)
endif()

if(BUILD_CPP26 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cpp26/CMakeLists.txt")
    add_subdirectory(cpp26)
endif()

if(BUILD_CROSS_CUTTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cross_cutting/CMakeLists.txt")
    add_subdirectory(cross_cutting)
endif()

if(BUILD_SANDBOX AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sandbox/CMakeLists.txt")
    add_subdirectory(sandbox)
endif()

# Shared libraries (if any)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/CMakeLists.txt")
    add_subdirectory(libs)
endif()

# -----------------------------------------------------------------------------
# Print configuration summary
# -----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "=== cpp-playground Configuration ===")
message(STATUS "Build type:      ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler:        ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++17 exercises: ${BUILD_CPP17}")
message(STATUS "C++20 exercises: ${BUILD_CPP20}")
message(STATUS "C++23 exercises: ${BUILD_CPP23}")
message(STATUS "C++26 experiments: ${BUILD_CPP26}")
message(STATUS "Cross-cutting:   ${BUILD_CROSS_CUTTING}")
message(STATUS "Sandbox:         ${BUILD_SANDBOX}")
message(STATUS "====================================")
message(STATUS "")