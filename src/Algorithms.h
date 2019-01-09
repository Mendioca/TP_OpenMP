#pragma once

#define N_LETTERS 26

namespace CharMatrixHandling {
    // void setCount(int* count);

    void countLetters_S(int size, long *count, char **matrix);

    void countLetters_P(int size, long *count, char **matrix);

    void countLettersByVector_P(int size, long *count, char **matrix);

    void countLettersTask_P(int size, long *count, char **matrix);
}

namespace MatrixHandling {
    double autoAddMatrix_S(int size_x, int size_y, const double **mi);

    void addMatrices_S(int size_x, int size_y, double **mr, const double **m1, const double **m2);

    void multMatriceNumber_S(int size_x, int size_y, double **mr, const double **mi, double number);

    void multMatrices_S(int size_x1, int size_x2, int size_y1, double **mr, double **m1, double **m2);

    double autoAddMatrix_P(int size_x, int size_y, const double **mi);

    void addMatrices_P(int size_x, int size_y, double **mr, const double **m1, const double **m2);

    void multMatriceNumber_P(int size_x, int size_y, double **mr, const double **mi, double number);

    void multMatrices_P(int size_x1, int size_x2, int size_y1, double **mr, double **m1, double **m2);
}

namespace VectorHandling {
    double autoAdd_S(int size, const double *vector);

    void addVectors_S(int size, double *v, const double *v1, const double *v2);

    void multVectorByNumber_S(int size, double *v, const double *v1, double number);

    double scalar_product_S(int size, double *v1, double *v2);

    double autoAdd_P(int size, const double *vector);

    void addVectors_P(int size, double *v, const double *v1, const double *v2);

    void multVectorByNumber_P(int size, double *v, const double *v1, double number);

    double scalar_product_P(int size, double *v1, double *v2);
}

namespace MatrixVectorHandling {
    void matrixMultVect_S(int size_x, int size_y, double *vr, const double **mi, const double *vi);

    void matrixMultVect_P(int size_x, int size_y, double *vr, const double **mi, const double *vi);
}