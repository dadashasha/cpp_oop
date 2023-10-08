cmake_minimum_required(VERSION 3.23)
project(flat_map)

set(CMAKE_CXX_STANDARD 20)

add_executable(flat_map main.cpp flat_map.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(flat_map_test flat_map.cpp tests.cpp)

target_link_libraries(flat_map_test gtest_main)
