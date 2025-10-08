#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

const int m = 3;

int thread_count;

int A[m][m] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
};

int x[m] = {1,
            2,
            3};

int y[m] = {};

void* pth_mat_vect(void* rank);

int main(int argc, char *argv[]) {

    long thread; //variable for thread amount

    thread_count = strtol(argv[1], NULL, 10); //read the amount of threads.

    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));   //thread_handler

    for (thread = 0; thread < thread_count; thread++) {
        printf("Thread %ld\n", thread);
        pthread_create(&thread_handles[thread], NULL, pth_mat_vect, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", y[i]);
    }

    free(thread_handles);

    return 0;
}

void* pth_mat_vect(void* rank) {
    long my_rank = (long) rank;
    int local_m = m/thread_count;
    int first_row = my_rank * local_m;

    int last_row = (my_rank + 1) * local_m - 1;

    for (int i = first_row; i <= last_row; i++) {
        y[i] = 0;
        for (int j = 0; j < m; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return NULL;
}
