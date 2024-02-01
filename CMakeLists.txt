cmake_minimum_required(VERSION 3.13.4)

project(liboberon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX)
set(CMAKE_C)
find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")

include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
link_directories("${LLVM_LIBRARY_DIR}")

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(liboberon)
add_subdirectory(lloberon)
add_subdirectory(tests)
add_subdirectory(modules)