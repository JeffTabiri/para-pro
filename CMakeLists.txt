cmake_minimum_required(VERSION 3.16...4.0)
project(pthreads)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)

add_executable(pthreads main.c)
add_executable(matrix-serial matrix-serial.c)
add_executable(matrix-parallel matrix-parallel.c)
add_executable(matrix-vector-serial matrix-vector-serial.c)
add_executable(matrix-vector-parallel matrix-vector-parallel.c)
add_executable(calculate-pi calculate-pi.c)
add_executable(busy-wait-barrier-impl busy-wait-barrier-impl.c)
add_executable(semaphore-barrier-impl semaphore-barrier-impl.c)
add_executable(openmp openmp-example.c)
add_executable(openmp-trapezoid openmp-trapezoid.c)

target_link_libraries(openmp PUBLIC OpenMP::OpenMP_C)
target_link_libraries(openmp-trapezoid PRIVATE OpenMP::OpenMP_C)

target_compile_options(openmp PUBLIC -I/opt/homebrew/opt/libomp/include)
target_compile_options(openmp PUBLIC -L/opt/homebrew/opt/libomp/lib)

