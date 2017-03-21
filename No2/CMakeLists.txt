cmake_minimum_required(VERSION 3.6)
project(No2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp stack.h queue.h)
add_executable(No2 ${SOURCE_FILES})
