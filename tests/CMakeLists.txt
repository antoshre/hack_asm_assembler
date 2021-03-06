cmake_minimum_required(VERSION 3.15)
project(tests)

#set(CMAKE_CXX_FLAGS "--coverage")
add_executable(all_basic_tests string_utils.cpp atype.cpp ltype.cpp ctype.cpp btype.cpp)

add_executable(file_comparison_tests compare_with_hack.cpp)

find_package(GTest)
if (NOT GTEST_FOUND)
    message(STATUS "GTest package not found, pulling from remote")
    #Make GTest targets available
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.10.0
    )
    #Disable GMock, it isn't used
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    #Populate gtest gtest_main targets of googletest project
    FetchContent_MakeAvailable(googletest)
endif()


target_link_libraries(all_basic_tests hack::assembler gtest gtest_main)
target_link_libraries(file_comparison_tests hack::assembler gtest gtest_main)
