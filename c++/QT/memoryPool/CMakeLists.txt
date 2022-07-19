cmake_minimum_required(VERSION 3.21)
project(memoryPool)

set(CMAKE_CXX_STANDARD 14)

add_executable(memoryPool main.cpp TestStack.h MemoryPool.h)
