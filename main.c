#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int thread_count;

void* Hello(void* rank);

struct thread_args {
    long my_rank;
    char *task_name;
};


int main(int argc, char* argv[]) {

    long thread;

    pthread_t* thread_handles;

    thread_count = strtol(argv[1], NULL, 10);

    thread_handles = malloc (thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++) {
        struct thread_args *thread_args = malloc(sizeof(struct thread_args));

        thread_args->my_rank = thread;
        thread_args->task_name = "Hello task;";

        pthread_create(&thread_handles[thread], NULL, Hello, thread_args);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }


    free(thread_handles);

    return 0;
}

void* Hello(void* args) {
    struct thread_args* thread_args = (struct  thread_args*) args;

    printf("Hello from thread: %ld.\n", thread_args->my_rank);

    return NULL;
}