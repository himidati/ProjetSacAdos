cmake_minimum_required(VERSION 3.5)

project(ProjetSacAdos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjetSacAdos  src/Test.cpp  src/KpSolver.cpp src/KpSolverGreedy.cpp )
