cmake_minimum_required(VERSION 3.15)
project(tests)

add_executable(all_tests string_utils.cpp atype.cpp ltype.cpp ctype.cpp btype.cpp compare_with_hack.cpp)
target_link_libraries(all_tests hack_assembler)

find_package(GTest)
if (GTEST_FOUND)
    target_link_libraries(all_tests ${GTEST_BOTH_LIBRARIES})
else()
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

    target_link_libraries(all_tests gtest gtest_main)
endif()



