#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Timer.h"
#include "Algorithms.h"

void init_matrix(int size, char **&matrix, unsigned int seed) {
    if (matrix) {
        for (int i = 0; i < size; ++i)
            if(matrix[i]) delete[] matrix[i];
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

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough args\n");
        return 0;
    }

    unsigned int seed;

    argc > 3
    ? seed = atoi(argv[3])
    : seed = DEFAULT_SEED;

    int size = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);

    char **matrix = nullptr;

    // matrix is reallocated each time to prevent cashing mechanism
    init_matrix(size, matrix, seed);

    long count[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_S(size, count, matrix);
    long time_span_seq = Timer::stop();

    init_matrix(size, matrix, seed);

    long count_parallel_naive[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_P(size, count_parallel_naive, matrix);
    long time_span_parallel_naive = Timer::stop();
    bool parallel_naive_true = isEqual(count, count_parallel_naive);

    init_matrix(size, matrix, seed);

    long count_parallel_smart[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLettersByVector_P(size, count_parallel_smart, matrix);
    long time_span_parallel_smart = Timer::stop();
    bool parallel_smart_true = isEqual(count, count_parallel_smart);

    init_matrix(size, matrix, seed);

    long count_parallel_task[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLettersTask_P(size, count_parallel_task, matrix);
    long time_span_parallel_task = Timer::stop();
    bool parallel_task_true = isEqual(count, count_parallel_task);

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