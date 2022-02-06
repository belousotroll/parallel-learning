project(MPI)

find_package(MPI REQUIRED)
if(MPI_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_C_FLAGS}")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MPI_CXX_FLAGS}")
endif()

add_subdirectory(laboratory_work_5)
add_subdirectory(laboratory_work_6)