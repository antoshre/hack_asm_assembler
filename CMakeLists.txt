cmake_minimum_required(VERSION 3.15)
project(hack_to_cpp)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

find_package(LLVM REQUIRED)

set(SOURCES main.cpp
        src/AsmFile.cpp
        src/AST.cpp
        src/SymbolTable.cpp
        src/Instructions/A_Type.cpp
        src/Instructions/L_Type.cpp
        src/Instructions/C_Type.cpp
        )

add_executable(hack_to_cpp ${SOURCES})
target_include_directories(hack_to_cpp
        PRIVATE src
        PUBLIC include
        )
target_link_libraries(hack_to_cpp frozen ctre llvm)