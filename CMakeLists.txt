cmake_minimum_required(VERSION 4.2)
project(Collection_CPP_Algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(graph_algorithms graph_algorithms/main.cpp)
add_executable(sorting_searching sorting_searching/main.cpp)
add_executable(complexity_algorithms complexity_algorithms/main.cpp)