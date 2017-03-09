cmake_minimum_required(VERSION 3.6)
project(No1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cc include/node.h include/linked_list.h)
add_executable(No1 ${SOURCE_FILES})
