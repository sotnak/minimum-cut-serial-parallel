cmake_minimum_required(VERSION 3.0)
project(pdp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -pedantic")

add_executable(pdp src/main.cpp src/Problem.cpp src/headers/Problem.h src/Solution.cpp src/headers/Solution.h src/solvers/headers/ASolver.h src/Configuration.cpp src/headers/Configuration.h src/solvers/Asolver.cpp src/solvers/BBSolver.cpp src/solvers/headers/BBSolver.h src/ArgGetter.cpp src/headers/ArgGetter.h)
