cmake_minimum_required(VERSION 3.20)
project(lab3_parallel_scheme_v1_)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab3_parallel_scheme_v1_ main.cpp)

if (MINGW)
    target_link_options(lab3_parallel_scheme_v1_ PRIVATE -static)
endif()