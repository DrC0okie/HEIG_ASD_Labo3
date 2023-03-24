cmake_minimum_required(VERSION 3.16)
project(ASD-Labos-2021)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(Testing-function main.cpp SortLib.h SortLibImpl.h some_bits.h)
add_executable(Generate-stats main2.cpp SortLib.h SortLibImpl.h some_bits.h)