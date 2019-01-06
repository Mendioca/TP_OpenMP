#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Algorithms.h"
#include "Timer.h"

#define SIZE 2

int main(int argc, char *argv[]) {
    srand(DEFAULT_SEED);
    int nb_iter = 5;

//    if (argc < 3) {
//        printf("Not enough args\n");
//        return 0;
//    }
//
//    int size = atoi(argv[2]);
//    int num_threads = atoi(argv[1]);
    omp_set_num_threads(4);
    double **m1 = Utils::mallocMatrix<double>(SIZE, SIZE);
    double **m2 = Utils::mallocMatrix<double>(SIZE, SIZE);
    double **mr_S = Utils::mallocMatrix<double>(SIZE, SIZE);
    double **mr_P = Utils::mallocMatrix<double>(SIZE, SIZE);

    Utils::generateMatrix(SIZE, SIZE, m1);
    Utils::generateMatrix(SIZE, SIZE, m2);

    Utils::printMatrix(SIZE, SIZE, m1);
    std::cout << std::endl;
    Utils::printMatrix(SIZE, SIZE, m2);

    MatrixHandling::multMatrices_S(SIZE, SIZE, SIZE, mr_S, m1, m2);
    MatrixHandling::multMatrices_P(SIZE, SIZE, SIZE, mr_P, m1, m2);
    std::cout << std::endl;
    Utils::printMatrix(SIZE, SIZE, mr_S);
    std::cout << std::endl;
    Utils::printMatrix(SIZE, SIZE, mr_P);

    return 0;
}
