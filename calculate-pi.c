#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n = 10000;
double sum = 0;
int thread_count;
pthread_mutex_t mutex;
void* pth_calc_pi(void* rank);

int main(int argc, char *argv[]) {
    double pi = 0;

    long thread; //variable for thread amount

    thread_count = strtol(argv[1], NULL, 10); //read the amount of threads.

    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));   //thread_handler
    pthread_mutex_init(&mutex, NULL);

    for (thread = 0; thread < thread_count; thread++) {
        printf("Thread %ld\n", thread);
        pthread_create(&thread_handles[thread], NULL, pth_calc_pi, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    pi = 4 * sum;

    printf("pi = %lf\n", pi);

    pthread_mutex_destroy(&mutex);
    free(thread_handles);

    return 0;

}

void* pth_calc_pi(void* rank) {

    long my_rank = (long) rank;

    int local_m = n/thread_count;

    int first_i = my_rank * local_m;

    int last_i = (my_rank + 1) * local_m - 1;

    double my_sum = 0;

    double factor;

    if (my_rank % 2 == 0) {
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (int i = first_i; i < last_i; i++, factor = -factor ) {
        my_sum += factor/(2 * i + 1);
    }

    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);
}
