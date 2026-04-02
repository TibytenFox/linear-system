#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix *MatrixInit(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    Matrix *result = (Matrix*)malloc(sizeof(Matrix));
    if (result == NULL) return NULL;

    result->data = (double**)malloc(rows * sizeof(double*));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        result->data[i] = (double*)malloc(cols * sizeof(double));
        if (result->data[i] == NULL) {
            for (int j = 0; j < i; j++) free(result->data[j]);
            free(result->data);
            free(result);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result->data[i][j] = 0.0;
        }
    }

    result->rows = rows;
    result->cols = cols;
    return result;
}

void MatrixDelete(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

Matrix *MatrixClone(Matrix *matrix) {
    if (matrix == NULL) return NULL;

    Matrix *clone = MatrixInit(matrix->rows, matrix->cols);
    if (clone == NULL) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            clone->data[i][j] = matrix->data[i][j];
        }
    }

    return clone;
}

double MatrixGet(Matrix *matrix, int index1, int index2) {
    if (index1 < 0 || index1 >= matrix->rows || index2 < 0 || index2 >= matrix->cols) {
        return 0.0; // или обработать ошибку по необходимости
    }
    return matrix->data[index1][index2];
}

int MatrixSet(Matrix *matrix, int index1, int index2, double value) {
    if (index1 < 0 || index1 >= matrix->rows || index2 < 0 || index2 >= matrix->cols) {
        return -1; // или обработать ошибку по необходимости
    }
    matrix->data[index1][index2] = value;
    return 0;
}

void MatrixSwapRows(Matrix *matrix, int row1, int row2) {
    if (row1 < 0 || row1 >= matrix->rows || row2 < 0 || row2 >= matrix->rows) {
        return; // или обработать ошибку по необходимости
    }
    double *temp = matrix->data[row1];
    matrix->data[row1] = matrix->data[row2];
    matrix->data[row2] = temp;
}

Vector *MatrixMultiplyVector(Matrix *matrix, Vector *vector) {
    if (matrix->cols != vector->size) return NULL;

    Vector *result = VectorInit(matrix->rows);
    if (result == NULL) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < matrix->cols; j++) {
            sum += MatrixGet(matrix, i, j) * VectorGet(vector, j);
        }
        VectorSet(result, i, sum);
    }

    return result;
}

void MatrixPrint(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf ", matrix->data[i][j]);
        }
        printf("\n");
    }
}