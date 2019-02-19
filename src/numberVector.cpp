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
    
    auto v1 = Utils::mallocVector<double>(size);
    auto v2 = Utils::mallocVector<double>(size);
    
    auto vr = Utils::mallocVector<double>(size);

    auto number = Utils::generateNumber<double>();

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

    //size,num_threads,vec_autoAdd,addVectors,multVecByNum,scalarProduct
    printf("%d,%d,%f,%f,%f,%f\n",
           size,
           num_threads,
           vec_autAdd_time,
           addVectors_time,
           multVectorByNumber_time,
           scalarProduct_time);

    return 0;
}

