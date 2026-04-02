#pragma once
#include "matrix.h"
#include "vector.h"

typedef struct LU {
    Matrix *L;
    Matrix *U;
} LU;

LU     *LUDecomposition(Matrix *A);
void    LUDelete(LU *lu);
Vector *LUSolve(LU *lu, Vector *b);