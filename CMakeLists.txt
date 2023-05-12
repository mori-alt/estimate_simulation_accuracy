cmake_minimum_required(VERSION 3.25)
project(estimate_simulation_accuracy)

set(CMAKE_CXX_STANDARD 20)

add_executable(estimate_simulation_accuracy main.cpp CsvData.h BRDF.h ./random/random.cpp ./random/random.h)

find_package(Eigen3 REQUIRED)
target_link_libraries("${CMAKE_PROJECT_NAME}" Eigen3::Eigen)

find_package(OpenMP)
if(OPENMP_CXX_FOUND)
    # add flags for OpenMP
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
