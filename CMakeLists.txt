cmake_minimum_required(VERSION 3.30)
project(AoC2024)

#find_package(MPI REQUIRED)
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

add_executable(AoC2024
        utils.cpp
        utils.h
        day6.cpp)

#target_link_libraries(AoC2024 ${MPI_C_LIBRARIES})