cmake_minimum_required(VERSION 3.0)
project(parallel-learning)

option(LAB_1 "Laboratory work 1" OFF)
option(LAB_2 "Laboratory work 2" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunreachable-code -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LAB_1)
    add_subdirectory(laboratory_work_1)
endif()

if(LAB_2)
    add_subdirectory(laboratory_work_2)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")