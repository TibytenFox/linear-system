#pragma once
typedef struct Vector{
    double *data;
    int size;
} Vector;

Vector *VectorInit(int size);
void    VectorDelete(Vector *vector);
Vector *VectorClone(Vector *vector);
double  VectorGet(Vector *vector, int index);
int     VectorSet(Vector *vector, int index, double value);
void    VectorSwap(Vector *vector, int index1, int index2);
void    VectorSubstract(Vector *vector1, Vector *vector2);
void    VectorPrint(Vector *vector);
