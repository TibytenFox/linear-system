#include <stddef.h>
#include <stdio.h>
#include "matrix.h"
#include "vector.h"
#include "gauss.h"
#include "lu.h"

void ManualInput() {
    int n;
    printf("Enter the size of the system (n): ");
    scanf("%d", &n);

    Matrix *A = MatrixInit(n, n);
    Vector *b = VectorInit(n);

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    if (b == NULL) {
        printf("Memory allocation failed.\n");
        MatrixDelete(A);
        return;
    }

    printf("Enter the coefficients of the matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A->data[i][j]);
        }
    }

    printf("Enter the constants vector b:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b->data[i]);
    }

    char type;
    printf("Choose the method (G for Gauss Elimination, P for Gauss Elimination with Pivoting, L for LU Decomposition and Solving): ");
    scanf(" %c", &type);

    if (type == 'G' || type == 'g') {
        Vector *solution = GaussElimination(A, b);
        if (solution != NULL) {
            printf("Solution:\n");
            VectorPrint(solution);
            VectorDelete(solution);
        } else {
            printf("No unique solution exists.\n");
        }
    } else if (type == 'P' || type == 'p') {
        Vector *solution = GaussEliminationWithPivoting(A, b);
        if (solution != NULL) {
            printf("Solution:\n");
            VectorPrint(solution);
            VectorDelete(solution);
        } else {
            printf("No unique solution exists.\n");
        }
    } else if (type == 'L' || type == 'l') {
        LU *lu = LUDecomposition(A);
        if (lu != NULL) {
            printf("L:\n");
            MatrixPrint(lu->L);
            printf("\n");
            printf("U:\n");
            MatrixPrint(lu->U);
            printf("\n");

            Vector *solution = LUSolve(lu, b);
            if (solution != NULL) {
                printf("Solution:\n");
                VectorPrint(solution);
                VectorDelete(solution);
            } 
            else {
                printf("No unique solution exists.\n");
            }
            LUDelete(lu);
        }
        else {
            printf("No unique solution exists.\n");
        }
    } else {
        printf("Invalid method choice.\n");
    }

    MatrixDelete(A);
    VectorDelete(b);
}

int main() {
    ManualInput();
    return 0;
}