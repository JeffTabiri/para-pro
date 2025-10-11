#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
#   include <omp.h>
#endif

void Hello(void) {
    #ifdef _OPENMP
        int rank = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
    #else
        int rank = 0;
        int thread_count = 1;
    #endif

    printf("Hello from thread %d of %d\n", rank, thread_count);
}


int main(int argc, char *argv[]) {
    int thread_count = strtol(argv[1], nullptr, 10);

#   pragma  omp parallel num_threads(thread_count)
    Hello();
    return 0;
}
