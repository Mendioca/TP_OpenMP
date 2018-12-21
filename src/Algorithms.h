#pragma once

namespace CharMatrixHandling {
    void countLetters_S(int size, int *count, char **matrix);

    void countLetters_P(int size, int *count, char **matrix);
}

namespace MatrixHandling {

}

namespace VectorHandling {
    void add_S(int size, double *v, const double *v1, const double *v2);

    double autoAdd_S(int size, const double *vector);

    void mult_S(int size, double *v, const double *v1, double number);

    double scalar_product_S(int size, double *v1, double *v2);

    void add_P(int size, double *v, const double *v1, const double *v2);

    double autoAdd_P(int size, const double *vector);

    void mult_P(int size, double *v, const double *v1, double number);

    double scalar_product_P(int size, double *v1, double *v2);
}

namespace MatrixVectorHandling {
    void matrixMultVect_S(int size_x, int size_y, double *vr, const double **mi, const double *vi);

    void matrixMultVect_P(int size_x, int size_y, double *vr, const double **mi, const double *vi);
}