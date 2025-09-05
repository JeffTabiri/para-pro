#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return x / 2;
}

/**
 * Calculates area under a function using the trapezoid rule.
 *
 * @param a is left endpoint.
 * @param b is the right endpoint.
 * @param n is an amount of intervals.
 * @param h is the distance between each interval.
 *
 * @return the area occupied from a to b with step h.
 */
double trapezoid(double a, double b, int n, double h) {

    double sum_y = 0;

    sum_y = (f(a) + f(b)) / 2.0; // Calculate the mean between a and b.

    for (int i = 1; i <= n - 1; i++) {
        double x = a + i * h;
        sum_y += f(x);
    }

    sum_y *= h;

    return sum_y;
}


int main() {

    int n = 200;
    double a = 0.0;
    double b = 3.0;
    double h = (b - a)/n;

    int rank;
    int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;

    double total_area = 0;
    double local_area = trapezoid(local_a, local_b, local_n, h);

    if (rank != 0) {
        MPI_Send(&local_area, 1, MPI_DOUBLE,0,0, MPI_COMM_WORLD);
    } else {

        total_area = local_area;

        for (int i = 1; i < size; i++) {
            MPI_Recv(&local_area, 1, MPI_DOUBLE,i,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_area += local_area;
        }

    }

    if (rank == 0) {
        printf("With n = %d trapezoids, our estimate \n", n);
        printf("of the integral from %f to %f = %.15e\n", a, b, total_area);
    }

    MPI_Finalize();

    return 0;
}
