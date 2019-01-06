#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Algorithms.h"
#include "Timer.h"

#define SIZE 5

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
//    double **m1 = Utils::mallocMatrix<double>(SIZE, SIZE);
//    double **m2 = Utils::mallocMatrix<double>(SIZE, SIZE);
//    double **mr_S = Utils::mallocMatrix<double>(SIZE, SIZE);
//    double **mr_P = Utils::mallocMatrix<double>(SIZE, SIZE);
//
//    Utils::generateMatrix(SIZE, SIZE, m1);
//    Utils::generateMatrix(SIZE, SIZE, m2);
//
//    Utils::printMatrix(SIZE, SIZE, m1);
//    std::cout << std::endl;
//    Utils::printMatrix(SIZE, SIZE, m2);
//
//    MatrixHandling::multMatrices_S(SIZE, SIZE, SIZE, mr_S, m1, m2);
//    MatrixHandling::multMatrices_P(SIZE, SIZE, SIZE, mr_P, m1, m2);
//    std::cout << std::endl;
//    Utils::printMatrix(SIZE, SIZE, mr_S);
//    std::cout << std::endl;
//    Utils::printMatrix(SIZE, SIZE, mr_P);

    auto *v1 = Utils::mallocVector<double>(SIZE);
    auto *v2 = Utils::mallocVector<double>(SIZE);

    Utils::generateVector(SIZE, v1);
    Utils::generateVector(SIZE, v2);

    Utils::printVector(SIZE, v1);
    std::cout << std::endl;
    Utils::printVector(SIZE, v2);

    double res_S = VectorHandling::scalar_product_S(SIZE, v1, v2);
    double res_P = VectorHandling::scalar_product_P(SIZE, v1, v2);

    std::cout << "results : sequential = " << res_S << " | parallel = " << res_P << std::endl;

    return 0;
}
