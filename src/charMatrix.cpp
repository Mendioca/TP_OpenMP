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

void printResult(const long *count) {
    int disp_count = 0;
    for (int i = 0; i < N_LETTERS; ++i) {
        if (count[i] > 0) {
            disp_count++;
            std::cout << (char) (i + 'a') << ":" << count[i];

            if (disp_count == 4) {
                std::cout << std::endl;
                disp_count = 0;
            } else
                std::cout << " | ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    srand(DEFAULT_SEED);

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

    init_matrix(size, matrix, seed);

    long count[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_S(size, count, matrix);
    long time_span = Timer::stop();

    init_matrix(size, matrix, seed);

    long countParallel_naive[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_P(size, countParallel_naive, matrix);
    long time_span_parallel_naive = Timer::stop();

    init_matrix(size, matrix, seed);

    long countParallel_smart[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLettersByVector_P(size, countParallel_smart, matrix);
    long time_span_parallel_smart = Timer::stop();

    init_matrix(size, matrix, seed);

    long countParallel_task[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLettersTask_P(size, countParallel_task, matrix);
    long time_span_parallel_task = Timer::stop();


    std::cout << "seq time = " << time_span << "µs" << std::endl;

    if (isEqual(count, countParallel_naive)) {
        std::cout << "Results using naive parallelism are correct" << std::endl;
        std::cout << "naive par time = " << time_span_parallel_naive << "µs" << std::endl;
    } else {
        std::cout << "Results using naive parallelism are NOT correct" << std::endl;
        printResult(count);
        std::cout << std::endl;
        printResult(countParallel_naive);
        std::cout << "=========================================" << std::endl;
    }

    if (isEqual(count, countParallel_smart)) {
        std::cout << "Results using smart parallelism are correct" << std::endl;
        std::cout << "smart par time = " << time_span_parallel_smart << "µs" << std::endl;
    } else {
        std::cout << "Results using smart parallelism are NOT correct" << std::endl;
        printResult(count);
        std::cout << std::endl;
        printResult(countParallel_smart);
        std::cout << "=========================================" << std::endl;
    }

    if (isEqual(count, countParallel_task)) {
        std::cout << "Results using task parallelism are correct" << std::endl;
        std::cout << "task par time = " << time_span_parallel_task << "µs" << std::endl;
    } else {
        std::cout << "Results using task parallelism are NOT correct" << std::endl;
        printResult(count);
        std::cout << std::endl;
        printResult(countParallel_task);
        std::cout << "=========================================" << std::endl;
    }

    return 0;
}