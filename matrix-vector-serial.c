#include <stdio.h>

int main(int argc, char *argv[]) {

    const int m = 3;

    int A[m][m] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    int x[m] = {1, 2, 3};

    int y[m] = {};

    for (int i = 0; i < m; i++) {
        y[i] = 0;

        for (int j = 0; j < m; j++) {
            y[i] += A[i][j] * x[j];
        }

    }

    for (int i = 0; i < m; i++) {
        printf("%d ", y[i]);
    }
    return 0;
}
