cmake_minimum_required(VERSION 3.13.4)

project(lloberon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX)

find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")

include_directories("${LLVM_INCLUDE_DIR}")
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(liboberon)
add_subdirectory(lloberon)
add_subdirectory(tests)
add_subdirectory(modules)