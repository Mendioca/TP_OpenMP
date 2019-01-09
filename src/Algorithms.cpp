#include <omp.h>
#include "Algorithms.h"

namespace CharMatrixHandling {
    static void setCount_S(int *count) {
        for (int i = 0; i < N_LETTERS; ++i) count[i] = 0;
    }

    static void setCount_P(int *count) {
#pragma omp parallel for
        for (int i = 0; i < N_LETTERS; ++i) count[i] = 0;
    }

    void countLetters_S(int size, int *count, char **matrix) {
        setCount_S(count);
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                count[matrix[r][c] - 'a']++;
            }
        }
    }

    void countLetters_P(int size, int *count, char **matrix) {
        setCount_P(count);
#pragma omp parallel for collapse(2)
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                int index = matrix[r][c] - 'a';
#pragma omp atomic
                ++count[index];
            }
        }
    }

    static void countInVector(int size, int *count, const char *vector) {
        for (int i = 0; i < size; ++i) {
#pragma omp atomic
            ++count[vector[i] - 'a'];
        }
    }

    void countLetterByVector_P(int size, int *count, char **matrix) {
        setCount_P(count);
#pragma omp parallel for
        for (int r = 0; r < size; ++r) {
            countInVector(size, count, matrix[r]);
        }
    }
}

namespace MatrixHandling {
    double autoAddMatrix_S(int size_x, int size_y, const double **mi) {
        double sum = 0;
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                sum += mi[i][j];
            }
        }
        return sum;
    }

    void addMatrices_S(int size_x, int size_y, double **mr, const double **m1, const double **m2) {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                mr[i][j] = m1[i][j] + m2[i][j];
            }
        }
    }

    void multMatriceNumber_S(int size_x, int size_y, double **mr, const double **mi, double number) {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                mr[i][j] = mi[i][j] * number;
            }
        }
    }

    void multMatrices_S(int size_x1, int size_x2, int size_y1, double **mr, double **m1, double **m2) {
        for (int col = 0; col < size_x2; ++col) {
            for (int row = 0; row < size_y1; ++row) {
                double partial_sum = 0;
                for (int i = 0; i < size_x1; ++i) {
                    partial_sum += m1[row][i] * m2[i][col];
                }
                mr[row][col] = partial_sum;
            }
        }
    }

    double autoAddMatrix_P(int size_x, int size_y, const double **mi) {
        double sum = 0;
#pragma omp parallel for collapse(2) reduction(+:sum)
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                sum += mi[i][j];
            }
        }
        return sum;
    }

    void addMatrices_P(int size_x, int size_y, double **mr, const double **m1, const double **m2) {
#pragma omp parallel for collapse(2)
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                mr[i][j] = m1[i][j] + m2[i][j];
            }
        }
    }

    void multMatriceNumber_P(int size_x, int size_y, double **mr, const double **mi, double number) {
#pragma omp parallel for collapse(2)
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                mr[i][j] = mi[i][j] * number;
            }
        }
    }

    void multMatrices_P(int size_x1, int size_x2, int size_y1, double **mr, double **m1, double **m2) {
#pragma omp parallel for collapse(2)
        for (int col = 0; col < size_x2; ++col) {
            for (int row = 0; row < size_y1; ++row) {
                double partial_sum = 0;
#pragma omp parallel for reduction(+:partial_sum)
                for (int i = 0; i < size_x1; ++i) {
                    partial_sum += m1[row][i] * m2[i][col];
                }
                mr[row][col] = partial_sum;
            }
        }
    }
}

namespace VectorHandling {
    double autoAdd_S(int size, const double *vector) {
        double sum = 0;

        for (int i = 0; i < size; i++) {
            sum += vector[i];
        }
        return sum;
    }

    void addVectors_S(int size, double *v, const double *v1, const double *v2) {
        for (int i = 0; i < size; i++) {
            v[i] = v1[i] + v2[i];
        }
    }

    void multVectorByNumber_S(int size, double *v, const double *v1, double number) {
        for (int i = 0; i < size; i++) {
            v[i] = number * v1[i];
        }
    }

    double scalar_product_S(int size, double *v1, double *v2) {
        double partial_sum = 0;
        for (int i = 0; i < size; ++i) {
            partial_sum += v1[i] * v2[i];
        }
        return partial_sum;
    }

    double autoAdd_P(int size, const double *vector) {
        double sum = 0;

#pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < size; i++) {
            sum += vector[i];
        }
        return sum;
    }

    void addVectors_P(int size, double *v, const double *v1, const double *v2) {
#pragma omp parallel for
        for (int i = 0; i < size; i++) {
            v[i] = v1[i] + v2[i];
        }
    }

    void multVectorByNumber_P(int size, double *v, const double *v1, double number) {
#pragma omp parallel for
        for (int i = 0; i < size; i++) {
            v[i] = number * v1[i];
        }
    }

    double scalar_product_P(int size, double *v1, double *v2) {
        double partial_sum = 0;
#pragma omp parallel for reduction(+:partial_sum)
        for (int i = 0; i < size; ++i) {
            partial_sum += v1[i] * v2[i];
        }
        return partial_sum;
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

