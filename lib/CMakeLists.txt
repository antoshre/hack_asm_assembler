cmake_minimum_required(VERSION 3.15)
project(hack_assembler_lib)

set(LIB_SOURCES
        src/AsmFile.cpp
        src/AST.cpp
        src/SymbolTable.cpp
        src/Instructions/A_Type.cpp
        src/Instructions/L_Type.cpp
        src/Instructions/C_Type.cpp
        src/Instructions/B_Type.cpp
        )

add_library(hack_assembler ${LIB_SOURCES})

target_link_libraries(hack_assembler PRIVATE frozen ctre)
target_include_directories(hack_assembler PRIVATE src
        PUBLIC include)
set_property(TARGET hack_assembler PROPERTY CXX_STANDARD 20)
set_property(TARGET hack_assembler PROPERTY CXX_STANDARD_REQUIRED ON)