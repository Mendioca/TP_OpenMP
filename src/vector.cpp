#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <omp.h>

#include "Utils.h"

#define SEED 1337

using namespace std::chrono;

/////////////////VECTOR//////////////////////////

void addVectors(int size, double *v, const double *v1, const double *v2) {
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        v[i] = v1[i] + v2[i];
    }
}

double autoAdd(int size, const double *vector) {
    double sum = 0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += vector[i];
    }

    return sum;
}

void mult(int size, double *v, const double *v1, double number) {
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        v[i] = number * v1[i];
    }
}

///////////////////MAT * VECT////////////////////////

void matrixMultVect(int size_x, int size_y, double *vr, const double **mi, const double *vi) {
#pragma omp parallel for
    for (int i = 0; i < size_x; i++) {
        double partial_sum = 0;
#pragma omp parallel for reduction(+:partial_sum)
        for (int j = 0; j < size_y; j++) {
            partial_sum += (mi[i][j] * vi[j]);
        }
        vr[i] = partial_sum;
    }
}

///////////////////MATRIX////////////////////////////

void addMatrices(int size_x, int size_y, double **mr, const double **m1, const double **m2) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            mr[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void multMatricesNumber(int size_x, int size_y, double **mr, const double **mi, double number) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            mr[i][j] = mi[i][j] * number;
        }
    }
}

double autoAddMatrix(int size_x, int size_y, const double **mi) {
    double sum = 0;
#pragma omp parallel for collapse(2) reduction(+:sum)
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            sum += mi[i][j];
        }
    }
}

/////////////////////////////////////////////////////
///////////////////TESTS/////////////////////////////
/////////////////////////////////////////////////////

void testAutoAdds(int size, double *v, int nb_iter) {
    high_resolution_clock::time_point begin;
    high_resolution_clock::time_point end;
    long time_span = 0;
    double val;
    for (int i = 0; i < nb_iter; i++) {
        Utils::generateVector(size, v);

        begin = high_resolution_clock::now();

        val = autoAdd(size, v);

        end = high_resolution_clock::now();
        time_span += duration_cast<microseconds>(end - begin).count();
    }

    printf("auto addition took %f µs\n", (double) time_span / nb_iter);
}

void testAdds(int size, double *vr, double *v1, double *v2, int nb_iter) {
    high_resolution_clock::time_point begin;
    high_resolution_clock::time_point end;
    long time_span = 0;
    for (int i = 0; i < nb_iter; i++) {
        Utils::generateVector(size, v1);
        Utils::generateVector(size, v2);

        begin = high_resolution_clock::now();

        addVectors(size, vr, v1, v2);

        end = high_resolution_clock::now();
        time_span += duration_cast<microseconds>(end - begin).count();
    }

    printf("addition took %f µs\n", (double) time_span / nb_iter);
}

void testMult(int size, double *vr, double *vi, int nb_iter) {
    high_resolution_clock::time_point begin;
    high_resolution_clock::time_point end;
    long time_span = 0;
    for (int i = 0; i < nb_iter; i++) {
        Utils::generateVector(size, vi);
        double number = (double) rand() / RAND_MAX;
        begin = high_resolution_clock::now();

        mult(size, vr, vi, number);

        end = high_resolution_clock::now();
        time_span += duration_cast<microseconds>(end - begin).count();
    }

    printf("multiplication took %f µs\n", (double) time_span / nb_iter);
}

///////////////////////////////////////////////
////////////////////MAIN///////////////////////
///////////////////////////////////////////////

int main(int argc, char *argv[]) {
    srand(SEED);
    int nb_iter = 5;

    if (argc < 3) {
        printf("Not enough args\n");
        return 0;
    }

    int size = atoi(argv[2]);
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);
    auto *v1 = Utils::mallocVector<double>(size);
    auto *v2 = Utils::mallocVector<double>(size);
    auto *v3 = Utils::mallocVector<double>(size);

    //testAdds(size, v3, v1, v2, nb_iter);

    //testAutoAdds(size, v1, nb_iter);

    //testMult(size, v3, v1, nb_iter);

    delete[] v1;
    delete[] v2;
    delete[] v3;

    return 0;
}
