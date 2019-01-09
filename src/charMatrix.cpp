#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Timer.h"
#include "Algorithms.h"

bool isEqual(const int *count1, const int *count2) {
    for (int i = 0; i < N_LETTERS; ++i) {
        if (count1[i] != count2[i])
            return false;
    }
    return true;
}

void printResult(const int *count) {
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

    if (argc > 3) {
        srand(atoi(argv[3]));
    }

    int size = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);

    auto **matrix = Utils::mallocSquareMatrix<char>(size);
    Utils::generateSquareMatrix(size, matrix);

//    Utils::printMatrix<char>(size, size, matrix);

    int count[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_S(size, count, matrix);
    long time_span = Timer::stop();

    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    srand(DEFAULT_SEED);
    if (argc > 3) {
        srand(atoi(argv[3]));
    }

    matrix = Utils::mallocSquareMatrix<char>(size);
    Utils::generateSquareMatrix(size, matrix);

    int countParallel[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetters_P(size, countParallel, matrix);
    long time_span_parallel = Timer::stop();

    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    srand(DEFAULT_SEED);
    if (argc > 3) {
        srand(atoi(argv[3]));
    }

    matrix = Utils::mallocSquareMatrix<char>(size);
    Utils::generateSquareMatrix(size, matrix);

    int countParallel_2[N_LETTERS];
    Timer::start();
    CharMatrixHandling::countLetterByVector_P(size, countParallel_2, matrix);
    long time_span_parallel_2 = Timer::stop();

//    printResult(count);
//    std::cout << std::endl;
//    printResult(countParallel);
//    std::cout << std::endl;
//    printResult(countParallel_2);

    std::cout << "seq time = " << time_span << "µs" << std::endl;
    if (isEqual(count, countParallel)) {
        std::cout << "Results using parallelism are correct" << std::endl;
        std::cout << "par time = " << time_span_parallel << "ms" << std::endl;
    } else {
        std::cout << "Results using parallelism are NOT correct" << std::endl;
        printResult(count);
        std::cout << std::endl;
        printResult(countParallel);
        std::cout << "=========================================" << std::endl;
    }

    if (isEqual(count, countParallel_2)) {
        std::cout << "Results using parallelism2 are correct" << std::endl;
        std::cout << "par2 time = " << time_span_parallel_2 << "µs" << std::endl;
    } else {
        std::cout << "Results using parallelism2 are NOT correct" << std::endl;
        printResult(count);
        std::cout << std::endl;
        printResult(countParallel_2);
        std::cout << "=========================================" << std::endl;
    }

    return 0;
}