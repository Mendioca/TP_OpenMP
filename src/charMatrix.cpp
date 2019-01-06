#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Timer.h"
#include "Algorithms.h"

static const int N_LETTERS = 'z' - 'a' + 1;

bool isEqual(const int* count1, const int* count2) {
    for (int i = 0; i < N_LETTERS; ++i) {
        if(count1[i] != count2[i])
            return false;
    }
    return true;
}

void setCount(int* count) {
    for (int i = 0; i < N_LETTERS; ++i) {
        count[i] = 0;
    }
}

void printResult(const int* count) {
    int disp_count = 0;
    for (int i = 0; i < N_LETTERS; ++i) {
        if(count[i] > 0) {
            disp_count++;
            std::cout << (char) (i + 'a') << ":" << count[i];

            if(disp_count == 4) {
                std::cout << std::endl;
                disp_count = 0;
            }
            else
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

    if(argc > 3) {
        srand(atoi(argv[3]));
    }

    int size = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);

    auto **matrix = Utils::mallocSquareMatrix<char>(size);
    Utils::generateSquareMatrix(size, matrix);

//    Utils::printMatrix<char>(size, size, matrix);

    int count[N_LETTERS];
    setCount(count);
    Timer::start();
    CharMatrixHandling::countLetters_S(size, count, matrix);
    long time_span = Timer::stop();

    int countParallel[N_LETTERS];
    setCount(countParallel);
    Timer::start();
    CharMatrixHandling::countLetters_P(size, countParallel, matrix);
    long time_span_parallel = Timer::stop();

//    printResult(count);
//    std::cout << std::endl;
//    printResult(countParallel);

    if(isEqual(count, countParallel)) {
        std::cout << "Results are corrects" << std::endl;
        std::cout << "seq time = " << time_span << "ms | par time = " << time_span_parallel << "ms" << std::endl;
    }
    else
        std::cout << "Results are NOT corrects" << std::endl;

    return 0;
}