cmake_minimum_required(VERSION 3.6)
project(No1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cc node.h linked_list.h sequential_list.h)
add_executable(No1 ${SOURCE_FILES})
