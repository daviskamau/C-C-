#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <vector>
#include <thread>


using namespace std::chrono;
using namespace std;

#define NUM_THREADS 4

void randomVectorSingle(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // creates a random value that is less than 100
        vector[i] = rand() % 100;
    }
}


void randomVectorMulti(int vector[], int start, int end)
{
    for (int i = start; i < end; i++)
    {
        // creates a random value that is less than 100
        vector[i] = rand() % 100;
    }
}


void singleThread(unsigned long size){
    srand(time(0));

    int *v1, *v2, *v3;

    // starts the timer
    auto start = high_resolution_clock::now();

    //malloc to avoid using stack as this is too much data and needs to be in the heap
    v1 = (int *) malloc(size * sizeof(int *));
    v2 = (int *) malloc(size * sizeof(int *));
    v3 = (int *) malloc(size * sizeof(int *));


    randomVectorSingle(v1, size);

    randomVectorSingle(v2, size);


    // iterates over each vector and performs an operation
    for (int i = 0; i < size; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    auto stop = high_resolution_clock::now();

    // tells how much time has passed between start and stop
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by sequential function: "
         << duration.count() << " microseconds" << endl;

}

void threadTasks(int threadNum, unsigned long size, int* v1, int* v2, int* v3) {
    int slice = size / NUM_THREADS;
    int start = threadNum * slice;
    int end = start + slice;

    randomVectorMulti(v1, start, end);
    randomVectorMulti(v2, start, end);

    // iterates over each vector and performs an operation
    for (int i = start; i < end; i++)
    {
        v3[i] = v1[i] + v2[i];
    }
}

void multiThread(unsigned long size) {
    srand(time(0));

    int* v1, * v2, * v3;

    // starts the timer
    auto start = high_resolution_clock::now();

    //malloc to avoid using stack as this is too much data and needs to be in the heap
    v1 = (int*)malloc(size * sizeof(int*));
    v2 = (int*)malloc(size * sizeof(int*));
    v3 = (int*)malloc(size * sizeof(int*));

    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(std::thread(threadTasks, i, size, v1, v2, v3));
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }


    auto stop = high_resolution_clock::now();

    // tells how much time has passed between start and stop
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by parallel function: "
        << duration.count() << " microseconds" << endl;

}


int main() {
    unsigned long size = 10000000;

    singleThread(size);
    multiThread(size);
    
    system("pause");
}