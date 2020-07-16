cmake_minimum_required(VERSION 3.15)
project(tests)


add_executable(all_tests string_utils.cpp atype.cpp ltype.cpp ctype.cpp compare_with_hack.cpp)
target_link_libraries(all_tests hack_assembler gtest gtest_main)
