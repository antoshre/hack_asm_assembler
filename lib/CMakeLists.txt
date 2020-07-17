cmake_minimum_required(VERSION 3.15)
project(hack_assembler_lib)

set(LIB_SOURCES
        src/AsmFile.cpp
        src/AST.cpp
        src/SymbolTable.cpp
        src/Instructions/A_Type.cpp
        src/Instructions/L_Type.cpp
        src/Instructions/C_Type.cpp
        )

find_package(Boost REQUIRED)

add_library(hack_assembler ${LIB_SOURCES})

if (NOT TARGET ctre)
    message(FATAL_ERROR "CTRE could not be found. Did the submodule get initialized?")
endif ()
if (NOT TARGET frozen)
    message(FATAL_ERROR "Frozen not found. Did the submodule get initialized?")
endif ()

target_link_libraries(hack_assembler PRIVATE frozen ctre Boost::headers)
target_include_directories(hack_assembler PRIVATE src
        PUBLIC include)