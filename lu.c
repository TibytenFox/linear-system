#include <stdlib.h>
#include "lu.h"

LU *LUDecomposition(Matrix *A) {
    int n = A->rows;
    Matrix *L = MatrixInit(n, n);
    Matrix *U = MatrixClone(A);
    if (L == NULL || U == NULL) {
        MatrixDelete(L);
        MatrixDelete(U);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        MatrixSet(L, i, i, 1.0);
    }

    for (int i = 0; i < n; i++) {
        double pivot = MatrixGet(U, i, i);
        if (pivot == 0) {
            MatrixDelete(L);
            MatrixDelete(U);
            return NULL; // Вырожденная матрица
        }

        for (int j = i + 1; j < n; j++) {
            double factor = MatrixGet(U, j, i) / pivot;
            MatrixSet(L, j, i, factor);
            for (int k = i; k < n; k++) {
                double value = MatrixGet(U, j, k) - factor * MatrixGet(U, i, k);
                MatrixSet(U, j, k, value);
            }
        }
    }

    LU *lu = (LU *)malloc(sizeof(LU));
    if (lu == NULL) {
        MatrixDelete(L);
        MatrixDelete(U);
        return NULL;
    }
    lu->L = L;  
    lu->U = U;
    return lu;
}

void LUDelete(LU *lu) {
    if (lu != NULL) {
        MatrixDelete(lu->L);
        MatrixDelete(lu->U);
        free(lu);
    }
}

Vector *LUSolve(LU *lu, Vector *b) {
    int n = lu->L->rows;
    Matrix *L = lu->L;
    Matrix *U = lu->U;

    Vector *y = VectorInit(n);
    Vector *x = VectorInit(n);
    if (x == NULL || y == NULL) {
        VectorDelete(x);
        VectorDelete(y);
        return NULL;
    }

    // Прямая подстановка для решения Ly = b
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += MatrixGet(L, i, j) * VectorGet(y, j);
        }
        VectorSet(y, i, (VectorGet(b, i) - sum) / MatrixGet(L, i, i));
    }

    // Обратная подстановка для решения Ux = y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += MatrixGet(U, i, j) * VectorGet(x, j);
        }
        VectorSet(x, i, (VectorGet(y, i) - sum) / MatrixGet(U, i, i));
    }

    VectorDelete(y);
    return x;
}