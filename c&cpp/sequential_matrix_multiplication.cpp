#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono> 
#include <iomanip> 

using namespace std;
using namespace std::chrono;

const int N = 700; 

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

    auto start = high_resolution_clock::now(); 

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    ofstream outputFile("sequential_matrix_multiplication_result.txt");
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
