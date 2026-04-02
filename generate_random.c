#include <stdlib.h>
#include "generate_random.h"

#define MIN_RANDOM_VALUE -1.0
#define MAX_RANDOM_VALUE 1.0

time_t GenerateRandomSeed() {
    return time(NULL);
}

static double RandomDouble01() {
    return (double)random() / ((double)RAND_MAX + 1.0);
}

static double RandomDoubleRange(double min, double max) {
    return min + RandomDouble01() * (max - min);
}

Vector *GenerateVector(int size) {
    Vector *vec = VectorInit(size);
    if (vec == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        VectorSet(vec, i, RandomDoubleRange(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE));
    }
    return vec;
}

Matrix *GenerateMatrix(int rows, int cols) {
    Matrix *mat = MatrixInit(rows, cols);
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MatrixSet(mat, i, j, RandomDoubleRange(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE));
        }
    }
    return mat;
}