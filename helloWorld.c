#include <stdio.h>
#include <mpi.h>
#include <string.h>

const int MAX_STING =  100;

int main(void) {

    char greetings[MAX_STING];

    int rank; // The process rank.
    int size; // The number of processes.

    /*
     * Tells the MPI system to do all the necessary setup.
     * It will allocate storage for message buffers and
     * decide with process gets which rank.
    */
    MPI_Init(NULL, NULL);

    /*
     * These functions are getting information about their communicator
     * established by MPI_Init
     */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Returns process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Returns size

    // Single program, multiple data

    if (rank != 0) {
        sprintf(greetings, "Hello World from process %d of %d!", rank, size);

        // Sends a message for another process to receive.
        MPI_Send(greetings, strlen(greetings) + 1, MPI_CHAR, 0,0, MPI_COMM_WORLD);

    } else {
        printf("Greetings from process %d of %d! \n", rank, size);

        for (int i = 1; i < size; i++) {

            // Receives message from another process. If there are no processes, the program will block forever!
            MPI_Recv(greetings, MAX_STING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("%s\n", greetings);
        }
    }



    /*
     *Tells the MPI system that we are done using MPI, and
     * it should free any allocated resources.
    */
    MPI_Finalize();

    return 0;
}