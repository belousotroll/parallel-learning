message(STATUS "Current project: laboratory_work_5")

find_package(MPI REQUIRED)
if(MPI_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_C_FLAGS}")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MPI_CXX_FLAGS}")
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE MPI::MPI_CXX)
