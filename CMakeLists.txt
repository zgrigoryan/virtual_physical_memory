cmake_minimum_required(VERSION 3.17)
project(inlining_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(inlining leak_demo.cpp
                        fragmentation.cpp
                        stack_overflow.cpp
                        virt_memory_simulation.cpp)
