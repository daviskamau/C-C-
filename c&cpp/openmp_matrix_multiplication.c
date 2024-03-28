#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define N 700

int main() {
    int A[N][N];
    int B[N][N];
    int C[N][N];

    srand(time(0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    double duration = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

    FILE *outputFile = fopen("openmp_matrix_multiplication_result.txt", "w");
    if (outputFile != NULL) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                fprintf(outputFile, "%d ", C[i][j]);
            }
            fprintf(outputFile, "\n");
        }
        fclose(outputFile);
    }

    printf("Execution time: %.3f ms\n", duration);

    return 0;
}
