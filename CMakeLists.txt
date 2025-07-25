cmake_minimum_required(VERSION 3.17)
project(inlining_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(leak_demo leak_demo.cpp)
add_executable(fragmentation fragmentation.cpp)
add_executable(stack_overflow stack_overflow.cpp)
add_executable(virt_memory_simulation virt_memory_simulation.cpp)
