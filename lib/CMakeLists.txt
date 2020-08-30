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

add_library(${PROJECT_NAME} ${LIB_SOURCES})

#Project requires C++17 for string_view and variant
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE frozen ctre)
target_include_directories(${PROJECT_NAME} PRIVATE src
        PUBLIC include)

add_library(hack::assembler ALIAS ${PROJECT_NAME})