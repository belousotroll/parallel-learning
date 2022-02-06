project(laboratory_work_2)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
#target_compile_definitions(${PROJECT_NAME} PRIVATE OUTPUT)