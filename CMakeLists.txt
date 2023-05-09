cmake_minimum_required(VERSION 3.25)
project(estimate_simulation_accuracy)

set(CMAKE_CXX_STANDARD 20)

add_executable(estimate_simulation_accuracy main.cpp CsvData.h BRDF.h)
