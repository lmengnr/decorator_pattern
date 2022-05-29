cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)

project(cpp_simple_decorator)

find_package(Threads REQUIRED)

add_executable(
    decorator_stats_app
    src/main.cpp
    )

target_link_libraries(decorator_stats_app PRIVATE Threads::Threads)