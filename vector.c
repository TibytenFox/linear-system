#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

Vector *VectorInit(int size) {
    if (size <= 0) return NULL;

    Vector *result = (Vector*)malloc(sizeof(Vector));
    if (result == NULL) return NULL;

    result->data = (double*)malloc(size * sizeof(double));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        result->data[i] = 0.0;
    }

    result->size = size;
    return result;
}

void VectorDelete(Vector *vector) {
    free(vector->data);
    free(vector);
}

Vector *VectorClone(Vector *vector) {
    if (vector == NULL) return NULL;

    Vector *clone = VectorInit(vector->size);
    if (clone == NULL) return NULL;

    for (int i = 0; i < vector->size; i++) {
        clone->data[i] = vector->data[i];
    }

    return clone;
}

double VectorGet(Vector *vector, int index) {
    if (index < 0 || index >= vector->size) {
        return 0.0; // or handle error as needed
    }
    return vector->data[index];
}

int VectorSet(Vector *vector, int index, double value) {
    if (index < 0 || index >= vector->size) {
        return -1; // or handle error as needed
    }
    vector->data[index] = value;
    return 0;
}

void VectorSwap(Vector *vector, int index1, int index2) {
    if (index1 < 0 || index1 >= vector->size || index2 < 0 || index2 >= vector->size) {
        return; // or handle error as needed
    }
    double temp = vector->data[index1];
    vector->data[index1] = vector->data[index2];
    vector->data[index2] = temp;
}

void VectorSubstract(Vector *vector1, Vector *vector2) {
    if (vector1->size != vector2->size) return;

    for (int i = 0; i < vector1->size; i++) {
        VectorSet(vector1, i, VectorGet(vector1, i) - VectorGet(vector2, i));
    }
}

void VectorPrint(Vector *vector) {
    for (int i = 0; i < vector->size; i++) {
        printf("%lf ", vector->data[i]);
    }
    printf("\n");
}