#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
#   include <omp.h>
#endif

void Trap(float a, float b, int n, float *global_result_p);

int main(int argc, char *argv[]) {
    float global_result = 0.0;
    float a, b;
    int n = 0;

    int thread_count = strtol(argv[1], nullptr, 10);

    printf("Enter a, b, and n \n");
    scanf("%f %f %d", &a, &b, &n);

    //printf("N: %d\n", n);
#   pragma omp parallel num_threads(thread_count)
    Trap(a,b,n, &global_result);
    //after this method, program resumes to normal threading.

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.14e\n", a, b,global_result);
    return 0;
}


float f(float x) {
    return x * x;
}
void Trap(float a, float b, int n, float *global_result_p) {
    int rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    float h = (b - a) / n;
    int local_n = n / thread_count;
    float local_a = a + rank * local_n * h;
    float local_b = local_a + local_n * h;
    float result = (f(local_a) + f(local_b)) / 2.0;

    for (int i = 1; i <= local_n - 1; i++) {
        float x = local_a + i * h;
        result += f(x);
    }

    result = result * h;

#   pragma omp critical //critical point, addition happens sequentially.
    *global_result_p += result;
}