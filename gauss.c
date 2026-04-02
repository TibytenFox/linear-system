#include <stddef.h>
#include <math.h>
#include "gauss.h"

static void TransformToUpper(Matrix *A, Vector *b) {
    int n = A->rows;

    for (int i = 0; i < n; i++) {
        double pivot = MatrixGet(A, i, i);
        if (pivot == 0) return; // нет единственного решения

        for (int j = i + 1; j < n; j++) {
            double factor = MatrixGet(A, j, i) / pivot;
            for (int k = i; k < n; k++) {
                MatrixSet(A, j, k, MatrixGet(A, j, k) - factor * MatrixGet(A, i, k));
            }
            VectorSet(b, j, VectorGet(b, j) - factor * VectorGet(b, i));
        }
    }
}

static Vector *BackSubstitution(Matrix *A, Vector *b) {
    int n = A->rows;
    Vector *x = VectorInit(n);
    if (x == NULL) return NULL;

    for (int i = n - 1; i >= 0; i--) {
        double sum = VectorGet(b, i);
        for (int j = i + 1; j < n; j++) {
            sum -= MatrixGet(A, i, j) * VectorGet(x, j);
        }
        double pivot = MatrixGet(A, i, i);
        if (pivot == 0) {
            VectorDelete(x);
            return NULL; // нет единственного решения
        }
        VectorSet(x, i, sum / pivot);
    }

    return x;
}

Vector *GaussElimination(Matrix *A, Vector *b) {
    Matrix *U = MatrixClone(A);
    Vector *c = VectorClone(b);
    if (U == NULL || c == NULL) {
        MatrixDelete(U);
        VectorDelete(c);
        return NULL;
    }

    TransformToUpper(U, c);
    Vector *x = BackSubstitution(U, c);
    MatrixDelete(U);
    VectorDelete(c);
    return x;
}

Vector *GaussEliminationWithPivoting(Matrix *A, Vector *b) {
    int n = A->rows;

    Matrix *U = MatrixClone(A);
    Vector *c = VectorClone(b);
    if (U == NULL || c == NULL) {
        MatrixDelete(U);
        VectorDelete(c);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(MatrixGet(U, j, i)) > fabs(MatrixGet(U, maxRow, i))) {
                maxRow = j;
            }
        }

        if (maxRow != i) {
            MatrixSwapRows(U, i, maxRow);
            VectorSwap(c, i, maxRow);
        }
    }

    TransformToUpper(U, c);
    Vector *x = BackSubstitution(U, c);
    MatrixDelete(U);
    VectorDelete(c);
    return x;
}