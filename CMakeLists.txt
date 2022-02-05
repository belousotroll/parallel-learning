cmake_minimum_required(VERSION 3.0)
project(parallel-learning)

option(LAB_1 "Laboratory work 1" OFF)
option(LAB_2 "Laboratory work 2" OFF)
option(LAB_3 "Laboratory work 3" OFF)
option(LAB_4 "Laboratory work 4" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunreachable-code -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LAB_1)
    add_subdirectory(laboratory_work_1)
endif()

if(LAB_2)
    add_subdirectory(laboratory_work_2)
endif()

if(LAB_3)
    add_subdirectory(laboratory_work_3)
endif()

if(LAB_4)
    add_subdirectory(laboratory_work_4)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")