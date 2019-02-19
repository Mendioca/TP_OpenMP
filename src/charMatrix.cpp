#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Timer.h"
#include "Algorithms.h"

#define NBR_ITER 10

void init_matrix(int size, char **&matrix, unsigned int seed) {
    if (matrix) {
        for (int i = 0; i < size; ++i)
            if (matrix[i]) delete[] matrix[i];
        delete[] matrix;
    }

    srand(seed);

    matrix = Utils::mallocSquareMatrix<char>(size);
    Utils::generateSquareMatrix(size, matrix);
}

bool isEqual(const long *count1, const long *count2) {
    for (int i = 0; i < N_LETTERS; ++i) {
        if (count1[i] != count2[i])
            return false;
    }
    return true;
}

double measure(int size, long *count, char **matrix, void(*countLetters)(int, long *, char **)) {
    long total_time = 0;
    for (int i = 0; i < NBR_ITER; ++i) {
        Timer::start();
        countLetters(size, count, matrix);
        total_time += Timer::stop();
    }
    return (double) total_time / (double) NBR_ITER;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough args\n");
        return 0;
    }

    int size = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    unsigned int seed;
    argc > 3
    ? seed = atoi(argv[3])
    : seed = DEFAULT_SEED;
    omp_set_num_threads(num_threads);

    char **matrix = nullptr;

    // matrix is reallocated each time to prevent cashing mechanism
    // Not sure if this is really useful
    init_matrix(size, matrix, seed);

    long count[N_LETTERS];
    double time_span_seq = measure(size, count, matrix, CharMatrixHandling::countLetters_S);

    init_matrix(size, matrix, seed);

    long count_parallel_naive[N_LETTERS];
    double time_span_parallel_naive = measure(size, count_parallel_naive, matrix, CharMatrixHandling::countLetters_P);
    bool parallel_naive_true = isEqual(count, count_parallel_naive);

    init_matrix(size, matrix, seed);

    long count_parallel_smart[N_LETTERS];
    double time_span_parallel_smart = measure(size,
                                              count_parallel_smart,
                                              matrix,
                                              CharMatrixHandling::countLettersByVector_P);
    bool parallel_smart_true = isEqual(count, count_parallel_smart);

    init_matrix(size, matrix, seed);

    long count_parallel_task[N_LETTERS];
    double time_span_parallel_task = measure(size, count_parallel_task, matrix, CharMatrixHandling::countLettersTask_P);
    bool parallel_task_true = isEqual(count, count_parallel_task);

    //size,num_threads,seq_time,naive_parallel_time,smart_parallel_time,task_parallel_time

    std::cout << size << "," << num_threads << "," << time_span_seq << ",";
    if (parallel_naive_true)
        std::cout << time_span_parallel_naive;
    else
        std::cout << "N/A";
    std::cout << ",";

    if (parallel_smart_true)
        std::cout << time_span_parallel_smart;
    else
        std::cout << "N/A";
    std::cout << ",";

    if (parallel_task_true)
        std::cout << time_span_parallel_task;
    else
        std::cout << "N/A";
    std::cout << std::endl;

    return 0;
}