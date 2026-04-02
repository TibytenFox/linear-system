#include <stddef.h>
#include <stdio.h>
#include "matrix.h"
#include "vector.h"
#include "gauss.h"
#include "lu.h"

void ManualInput() {
    int n;
    printf("Введите размер системы (n): ");
    scanf("%d", &n);

    Matrix *A = MatrixInit(n, n);
    Vector *b = VectorInit(n);

    if (A == NULL) {
        printf("Ошибка выделения памяти.\n");
        return;
    }
    if (b == NULL) {
        printf("Ошибка выделения памяти.\n");
        MatrixDelete(A);
        return;
    }

    printf("Введите коэффициенты матрицы A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A->data[i][j]);
        }
    }

    printf("Вектор правой части b:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b->data[i]);
    }

    char type;
    printf("Выберите метод (G - Гаусс, P - Гаусс с выбором, L - LU-разложение): ");
    scanf(" %c", &type);

    if (type == 'G' || type == 'g') {
        Vector *solution = GaussElimination(A, b);
        if (solution != NULL) {
            printf("Решение:\n");
            VectorPrint(solution);
            VectorDelete(solution);
        } else {
            printf("Нет единственного решения.\n");
        }
    } else if (type == 'P' || type == 'p') {
        Vector *solution = GaussEliminationWithPivoting(A, b);
        if (solution != NULL) {
            printf("Решение:\n");
            VectorPrint(solution);
            VectorDelete(solution);
        } else {
            printf("Нет единственного решения.\n");
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
                printf("Решение:\n");
                VectorPrint(solution);
                VectorDelete(solution);
            } 
            else {
                printf("Нет единственного решения.\n");
            }
            LUDelete(lu);
        }
        else {
            printf("Нет единственного решения.\n");
        }
    } else {
        printf("Неверный выбор метода.\n");
    }

    MatrixDelete(A);
    VectorDelete(b);
}

int main() {
    ManualInput();
    return 0;
}