cmake_minimum_required(VERSION 4.0)
project(pthreads)

set(CMAKE_CXX_STANDARD 20)

add_executable(pthreads main.c)

add_executable(matrix-serial matrix-serial.c)
add_executable(matrix-parallel matrix-parallel.c)
add_executable(matrix-vector-serial matrix-vector-serial.c)
add_executable(matrix-vector-parallel matrix-vector-parallel.c)
