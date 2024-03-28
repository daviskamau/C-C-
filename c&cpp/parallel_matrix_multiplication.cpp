#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip> 
#include <pthread.h> 

using namespace std;
using namespace std::chrono;

const int N = 700; 
const int numberOfThreads = 8;

int A[N][N];
int B[N][N];
int C[N][N];

void* matrixMultiplicationChunk(void* specificThread) {
    int isolate = N / numberOfThreads;
    int startRow = static_cast<int>(reinterpret_cast<long>(specificThread)) * isolate;
    int endRow = startRow + isolate;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() % 10; 
            B[i][j] = rand() % 10; 
        }
    }

    auto start = high_resolution_clock::now();

    pthread_t threads[numberOfThreads];
    int specificThreads[numberOfThreads];

    for (int i = 0; i < numberOfThreads; ++i) {
        specificThreads[i] = i;
        int result = pthread_create(&threads[i], NULL, matrixMultiplicationChunk, reinterpret_cast<void*>(specificThreads[i]));
        if (result) {
            cout << "Error creating thread: " << result << endl;
            exit(-1);
        }
    }

    for (int i = 0; i < numberOfThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    ofstream outputFile("parallel_matrix_multiplication_result.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                outputFile << C[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    }

    cout << fixed << setprecision(3) << "Execution time: " << duration.count() / 1000.0 << " ms" << endl;

    return 0;
}
