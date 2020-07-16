cmake_minimum_required(VERSION 3.15)
project(hack_assembler_examples)

add_executable(print_ast print_ast.cpp)
target_link_libraries(print_ast hack_assembler)