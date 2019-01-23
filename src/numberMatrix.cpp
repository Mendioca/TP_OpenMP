#include <iostream>
#include <omp.h>

#include "Utils.h"
#include "Algorithms.h"
#include "Timer.h"

#define NBR_ITER 10

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

    srand(seed);
    omp_set_num_threads(num_threads);

    auto m1 = Utils::mallocMatrix<double>(size, size);
    auto m2 = Utils::mallocMatrix<double>(size, size);
    auto v1 = Utils::mallocVector<double>(size);
    auto v2 = Utils::mallocVector<double>(size);

    auto mr = Utils::mallocMatrix<double>(size, size);
    auto vr = Utils::mallocVector<double>(size);

    auto number = Utils::generateNumber<double>();

    Utils::generateMatrix(size, size, m1);
    Utils::generateMatrix(size, size, m2);

    Utils::generateVector(size, v1);
    Utils::generateVector(size, v2);

    ///VECTORS///
    double vec_autAdd_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            VectorHandling::autoAdd_P(size, v1);
            total_time += Timer::stop();
        }
        vec_autAdd_time = (double) total_time / (double) NBR_ITER;
    }

    double addVectors_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            VectorHandling::addVectors_P(size, vr, v1, v2);
            total_time += Timer::stop();
        }
        addVectors_time = (double) total_time / (double) NBR_ITER;
    }

    double multVectorByNumber_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            VectorHandling::multVectorByNumber_P(size, vr, v1, number);
            total_time += Timer::stop();
        }
        multVectorByNumber_time = (double) total_time / (double) NBR_ITER;
    }

    double scalarProduct_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            VectorHandling::scalar_product_P(size, vr, v1);
            total_time += Timer::stop();
        }
        scalarProduct_time = (double) total_time / (double) NBR_ITER;
    }

    ///MATRICES///
    double mat_autAdd_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            MatrixHandling::autoAddMatrix_P(size, size, m1);
            total_time += Timer::stop();
        }
        mat_autAdd_time = (double) total_time / (double) NBR_ITER;
    }

    double addMatrices_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            MatrixHandling::addMatrices_P(size, size, mr, m1, m2);
            total_time += Timer::stop();
        }
        addMatrices_time = (double) total_time / (double) NBR_ITER;
    }

    double multMatrixByNumber_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            MatrixHandling::multMatrixNumber_P(size, size, mr, m1, number);
            total_time += Timer::stop();
        }
        multMatrixByNumber_time = (double) total_time / (double) NBR_ITER;
    }

    double multMatrices_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            MatrixHandling::multMatrices_P(size, size, size, mr, m1, m2);
            total_time += Timer::stop();
        }
        multMatrices_time = (double) total_time / (double) NBR_ITER;
    }

    ///MATRIX&VECTORS
    double matrixMultVector_time;
    {
        long total_time = 0;
        for (int i = 0; i < NBR_ITER; ++i) {
            Timer::start();
            MatrixVectorHandling::matrixMultVect_P(size, size, vr, m1, v1);
            total_time += Timer::stop();
        }
        matrixMultVector_time = (double) total_time / (double) NBR_ITER;
    }
    
    //size,num_threads,vec_autoAdd,addVectors,multVecByNum,scalarProduct,mat_autoAdd,addMatrices,multMatByNum,multMatrices,matByVec
    printf("%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
            size,
            num_threads,
            vec_autAdd_time,
            addVectors_time,
            multVectorByNumber_time,
            scalarProduct_time,
            mat_autAdd_time,
            addMatrices_time,
            multMatrixByNumber_time,
            multMatrices_time,
            matrixMultVector_time);

    return 0;
}
