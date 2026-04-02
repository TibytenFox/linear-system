#pragma once
#include "vector.h"

typedef struct Matrix {
    double **data;
    int rows;
    int cols;
} Matrix;

Matrix *MatrixInit(int rows, int cols);
void    MatrixDelete(Matrix *matrix);
Matrix *MatrixClone(Matrix *matrix);
double  MatrixGet(Matrix *matrix, int index1, int index2);
int     MatrixSet(Matrix *matrix, int index1, int index2, double value);
void    MatrixSwapRows(Matrix *matrix, int row1, int row2);
Vector *MatrixMultiplyVector(Matrix *matrix, Vector *vector);
void    MatrixPrint(Matrix *matrix);