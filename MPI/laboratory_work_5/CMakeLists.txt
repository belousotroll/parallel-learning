project(laboratory_work_5)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE MPI::MPI_CXX)
