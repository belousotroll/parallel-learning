project(OpenMP)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O2")
endif()

add_subdirectory(laboratory_work_1)
add_subdirectory(laboratory_work_2)
add_subdirectory(laboratory_work_3)
add_subdirectory(laboratory_work_4)