#include <stdio.h>
#include <mpi.h>
#include <string.h>

const int MAX_STING =  100;
int main(void) {
    char greethings[MAX_STING];

    int rank, size;

    MPI_Init(NULL, NULL); //Tells the MPI sysgtem to do all of necessary setup.

    /*
     * Communicator is a collecton of processes that can
     * send messages to each other
     */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Greetings fom process %d of %d", rank, size);
        MPI_Send(greethings, strlen(greethings) + 1, MPI_CHAR, 0,0, MPI_COMM_WORLD);

    } else {
        printf("Greethings from process %d of %d! \n", rank, size);
        for (int i = 1; i < size; i++) {
            MPI_Recv(greethings, MAX_STING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greethings);
        }
    }



    MPI_Finalize(); //Were done using the MPI and an resources allocated are freed.

    return 0;
}