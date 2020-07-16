cmake_minimum_required(VERSION 3.15)
project(hack_to_cpp)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/frozen)
add_subdirectory(external/compile-time-regular-expressions)

add_subdirectory(lib)


option(BUILD_EXAMPLES "Build examples" OFF)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()