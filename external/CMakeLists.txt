cmake_minimum_required(VERSION 3.15)
project(external_deps)

include(FetchContent)
if (NOT TARGET frozen)
    FetchContent_Declare(
            frozen
            GIT_REPOSITORY https://github.com/serge-sans-paille/frozen.git
    )
    FetchContent_MakeAvailable(frozen)
endif()

if (NOT TARGET ctre)
    FetchContent_Declare(
            ctre
            GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
    )
    FetchContent_MakeAvailable(ctre)
endif()