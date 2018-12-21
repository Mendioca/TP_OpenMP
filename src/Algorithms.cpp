#include "Algorithms.h"

namespace CharMatrixHandling {
    void countLetters_S(int size, int *count, char **matrix) {
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                count[matrix[r][c] - 'a']++;
            }
        }
    }

    void countLetters_P(int size, int *count, char **matrix) {
#pragma omp parallel for collapse(2)
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                int index = matrix[r][c] - 'a';
#pragma omp atomic
                count[index]++;
            }
        }
    }
}

namespace VectorHandling {
    void add_S(int size, double *v, const double *v1, const double *v2) {
        for (int i = 0; i < size; i++) {
            v[i] = v1[i] + v2[i];
        }
    }

    double autoAdd_S(int size, const double *vector) {
        double sum = 0;

        for (int i = 0; i < size; i++) {
            sum += vector[i];
        }

        return sum;
    }

    void mult_S(int size, double *v, const double *v1, double number) {
        for (int i = 0; i < size; i++) {
            v[i] = number * v1[i];
        }
    }

    void add_P(int size, double *v, const double *v1, const double *v2) {
#pragma omp parallel for
        for (int i = 0; i < size; i++) {
            v[i] = v1[i] + v2[i];
        }
    }

    double autoAdd_P(int size, const double *vector) {
        double sum = 0;

#pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < size; i++) {
            sum += vector[i];
        }

        return sum;
    }

    void mult_P(int size, double *v, const double *v1, double number) {
#pragma omp parallel for
        for (int i = 0; i < size; i++) {
            v[i] = number * v1[i];
        }
    }
}

namespace MatrixVectorHandling {
    void matrixMultVect_S(int size_x, int size_y, double *vr, const double **mi, const double *vi) {
        for (int i = 0; i < size_x; i++) {
            double partial_sum = 0;
            for (int j = 0; j < size_y; j++) {
                partial_sum += (mi[i][j] * vi[j]);
            }
            vr[i] = partial_sum;
        }
    }

    void matrixMultVect_P(int size_x, int size_y, double *vr, const double **mi, const double *vi) {
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
}

