#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
    }
}

int main() {
    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    v1 = (int *)malloc(size * sizeof(int *));
    v2 = (int *)malloc(size * sizeof(int *));
    v3 = (int *)malloc(size * sizeof(int *));

    randomVector(v1, size);
    randomVector(v2, size);

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        v3[i] = v1[i] + v2[i];
    }

    gettimeofday(&stop, NULL);
    unsigned long long duration = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

    printf("Time taken by function: %llu microseconds\n", duration);

    return 0;
}
