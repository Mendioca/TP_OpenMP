#pragma once

#include <cstdlib>
#include <iostream>

class Utils {

public:
    template <typename T>
    static T* mallocVector(int size);

    template <typename T>
    static T** mallocMatrix(int n_rows, int n_columns);

    template <typename T>
    static T** mallocSquareMatrix(int size);

    template <typename T>
    static void generateVector(int size, T* vector);

    template <typename T>
    static void generateMatrix(int n_rows, int n_columns, T** matrix);

    template <typename T>
    static void generateSquareMatrix(int size, T** matrix);

    template <typename T>
    static void printVector(int size, T* vector);

    template <typename T>
    static void printMatrix(int n_rows, int n_columns, T** matrix);
};


static int randInt(int min, int max) {
    return rand() % (max - min) + min;
}

static char randLowerChar() {
    return (char) randInt((int) 'a', (int) 'z');
}

template<typename T>
T *Utils::mallocVector(int size) {
    return new T[size];
}

template<typename T>
void Utils::generateVector(int size, T *vector) {
    for (int i = 0; i < size; i++) {
        vector[i] = (T) rand();
    }
}

template<>
void Utils::generateVector<char>(int size, char *vector) {
    for (int i = 0; i < size; ++i) {
        vector[i] = randLowerChar();
    }
}

template<typename T>
void Utils::printVector(int size, T *vector) {
    for (int i = 0; i < size; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
T **Utils::mallocMatrix(int n_rows, int n_columns) {
    T **matrix = new T *[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        matrix[i] = Utils::mallocVector<T>(n_columns);
    }
    return matrix;
}

template<typename T>
T **Utils::mallocSquareMatrix(int size) {
    return Utils::mallocMatrix<T>(size, size);
}

template<typename T>
void Utils::generateMatrix(int n_rows, int n_columns, T **matrix) {
    for (int i = 0; i < n_rows; ++i) {
        Utils::generateVector<T>(n_columns, matrix[i]);
    }
}

template<typename T>
void Utils::generateSquareMatrix(int size, T **matrix) {
    Utils::generateMatrix(size, size, matrix);
}

template<typename T>
void Utils::printMatrix(int n_rows, int n_columns, T **matrix) {
    for (int i = 0; i < n_rows; ++i) {
        Utils::printVector<T>(n_columns, matrix[i]);
    }
}
