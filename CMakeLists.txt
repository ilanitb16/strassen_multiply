cmake_minimum_required(VERSION 3.27)
project(fast_matrix_multiplication C)

set(CMAKE_C_STANDARD 11)

include_directories(FMM)

add_executable(fast_matrix_multiplication
        FMM/fmm.c
        FMM/fmm.h
        FMM/main.c
        FMM/utilities.c)
