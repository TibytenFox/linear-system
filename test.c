#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generate_random.h"
#include "gauss.h"
#include "lu.h"
#include "vector.h"
#include "matrix.h"

#define MAXTRIX_SIZE 500

static void Test(int n) {
    Matrix *A = GenerateMatrix(n, n);
    Vector *b = GenerateVector(n);

    clock_t start_gauss, end_gauss;
    clock_t start_pivot, end_pivot;
    clock_t start_lu, end_lu;
    clock_t start_lu_solve, end_lu_solve;

    start_gauss = clock();
    Vector *solution_gauss = GaussElimination(A, b);
    end_gauss = clock();

    start_pivot = clock();
    Vector *solution_pivot = GaussEliminationWithPivoting(A, b);
    end_pivot = clock();   

    start_lu = clock();
    LU *lu = LUDecomposition(A);
    end_lu = clock();
    start_lu_solve = clock();
    Vector *solution_lu = LUSolve(lu, b);
    end_lu_solve = clock();

    printf("\n------------------------------\n");
    printf("Size: %d\n", n);
    printf("Gauss Elimination Time: %f seconds\n", (double)(end_gauss - start_gauss) / CLOCKS_PER_SEC);
    printf("Gauss Elimination with Pivoting Time: %f seconds\n", (double)(end_pivot - start_pivot) / CLOCKS_PER_SEC);
    printf("LU Decomposition Time: %f seconds\n", (double)(end_lu - start_lu) / CLOCKS_PER_SEC);
    printf("LU Solve Time: %f seconds\n", (double)(end_lu_solve - start_lu_solve) / CLOCKS_PER_SEC);
    printf("LU Decomposition + Solve Time: %f seconds\n", (double)(end_lu - start_lu + end_lu_solve - start_lu_solve) / CLOCKS_PER_SEC);
    printf("\n------------------------------\n");

    MatrixDelete(A);
    VectorDelete(b);
    VectorDelete(solution_gauss);
    VectorDelete(solution_pivot);
    LUDelete(lu);
    VectorDelete(solution_lu);
}

static void MultipleTests(int k) {
    Matrix *A = GenerateMatrix(MAXTRIX_SIZE, MAXTRIX_SIZE);

    Vector **b_set = (Vector **)malloc(k * sizeof(Vector *));
    for (int i = 0; i < k; i++) {
        b_set[i] = GenerateVector(MAXTRIX_SIZE);
    }

    clock_t start_gauss, end_gauss;
    clock_t start_pivot, end_pivot; 
    clock_t start_lu, end_lu;

    start_gauss = clock();
    for (int i = 0; i < k; i++) {
        Vector *solution_gauss = GaussElimination(A, b_set[i]);
        VectorDelete(solution_gauss);
    }
    end_gauss = clock();

    start_pivot = clock();
    for (int i = 0; i < k; i++) {
        Vector *solution_pivot = GaussEliminationWithPivoting(A, b_set[i]);
        VectorDelete(solution_pivot);
    }
    end_pivot = clock();

    start_lu = clock();
    LU *lu = LUDecomposition(A);
    for (int i = 0; i < k; i++) {
        Vector *solution_lu = LUSolve(lu, b_set[i]);
        VectorDelete(solution_lu);
    }
    end_lu = clock();

    printf("\n------------------------------\n");
    printf("Multiple Tests (k=%d)\n", k);
    printf("Gauss Elimination Total Time: %f seconds\n", (double)(end_gauss - start_gauss) / CLOCKS_PER_SEC);
    printf("Gauss Elimination with Pivoting Total Time: %f seconds\n", (double)(end_pivot - start_pivot) / CLOCKS_PER_SEC);
    printf("LU Decomposition + Solve Total Time: %f seconds\n", (double)(end_lu - start_lu) / CLOCKS_PER_SEC);
    printf("\n------------------------------\n");

    MatrixDelete(A);
    for (int i = 0; i < k; i++) {
        VectorDelete(b_set[i]);
    }
    LUDelete(lu);
    free(b_set);
}

static void PrintMenu() {
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║        Меню                                   ║\n");
    printf("╠═══════════════════════════════════════════════╣\n");
    printf("║ 1. Сравнение времени решения одной системы    ║\n");
    printf("║ 2. Множественные тесты                        ║\n");
    printf("║ 3. Проверка матрицей Гильберта                ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
}

static int ChooseSeed() {
    char choice;
    printf("Fix seed? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        time_t seed;
        printf("Your seed: ");
        scanf("%ld", &seed);
        srand(seed);
    } else if (choice == 'N' || choice == 'n') {
        time_t seed = GenerateRandomSeed();
        printf("Seed: %ld\n", seed);
        srand(seed);
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    return 0;
}

static Matrix *GenerateHilbertMatrix(int size) {
    Matrix *matrix = MatrixInit(size, size);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            MatrixSet(matrix, i, j, 1.0 / (i + j + 1));
        }
    }
    return matrix;
}

static Vector *GenerateOnesVector(int size) {
    Vector *vector = VectorInit(size);
    for (int i = 0; i < vector->size; i++) {
        VectorSet(vector, i, 1.0);
    }
    return vector;
}

static double CalculateRelativeError(Vector *computed, Vector *exact) {
    double numerator = 0.0;
    double denominator = 0.0;

    for (int i = 0; i < computed->size; i++) {
        numerator += (VectorGet(computed, i) - VectorGet(exact, i)) * (VectorGet(computed, i) - VectorGet(exact, i));
        denominator += VectorGet(exact, i) * VectorGet(exact, i);
    }

    return sqrt(numerator) / sqrt(denominator);
}

static double CalculateResidual(Matrix *H, Vector *x, Vector *b) {
    Vector *Hx = MatrixMultiplyVector(H, x);
    VectorSubstract(Hx, b);

    double sum = 0.0;
    for (int i = 0; i < Hx->size; i++) sum += VectorGet(Hx, i) * VectorGet(Hx, i);

    return sqrt(sum);
}

static void TestHilbert(int n) {
    Matrix *A = GenerateHilbertMatrix(n);
    Vector *x = GenerateOnesVector(n);
    Vector *b = MatrixMultiplyVector(A, x);

    Vector *x_gauss = GaussElimination(A, b);
    Vector *x_gauss_pivot = GaussEliminationWithPivoting(A, b);
    LU *lu = LUDecomposition(A);
    Vector *x_lu = LUSolve(lu, b);

    double re_gauss = CalculateRelativeError(x_gauss, x);
    double re_gauss_pivot = CalculateRelativeError(x_gauss_pivot, x);
    double re_lu = CalculateRelativeError(x_lu, x);
    double residual_gauss = CalculateResidual(A, x_gauss, b);
    double residual_gauss_pivot = CalculateResidual(A, x_gauss_pivot, b);
    double residual_lu = CalculateResidual(A, x_lu, b);

    printf("\n------------------------------\n");
    printf("Size: %d\n", n);
    printf("Gauss Elimination Relative error: %e\tResidual: %e\n", re_gauss, residual_gauss);
    printf("Gauss Elimination with Pivoting error: %e\tResidual: %e\n", re_gauss_pivot, residual_gauss_pivot);
    printf("LU Decomposition + Solve error: %e\tResidual: %e\n", re_lu, residual_lu);
    printf("\n------------------------------\n");

    MatrixDelete(A);
    VectorDelete(x);
    VectorDelete(b);
    VectorDelete(x_gauss);
    VectorDelete(x_gauss_pivot);
    LUDelete(lu);
    VectorDelete(x_lu);
}

int main() {
    if (ChooseSeed() != 0) return 1;

    PrintMenu();
    int type;
    printf("Выберите тип теста (1, 2 или 3): ");
    scanf("%d", &type);

    switch (type) {
        case 1:
        {
            int sizes[4] = {100, 200, 500, 1000};
            for (int i = 0; i < 4; i++) {
                Test(sizes[i]);
            }
            break;
        }
        case 2:
        {
            int amounts[3] = {1, 10, 100};
            for (int i = 0; i < 3; i++) {
                MultipleTests(amounts[i]);
            }
            break;
        }
        case 3:
        {
            int sizes[3] = {5, 10, 15};
            for (int i = 0; i < 3; i++) {
                TestHilbert(sizes[i]);
            }
            break;
        }
        default:
        {
            printf("Invalid choice. Exiting.\n");
            return 1;
        }
    }
    return 0;
}