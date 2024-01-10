cmake_minimum_required(VERSION 3.27)
project(GeneticATSPSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GeneticATSPSolver
        MatrixATSP.cpp
        MatrixATSP.h
        GeneticAlgorithm.h
        GeneticAlgorithm.cpp
        main.cpp
        Menu.h
        Menu.cpp
        PerformanceTest.h
        PerformanceTest.cpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")