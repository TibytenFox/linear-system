#pragma once
#include "matrix.h"
#include "vector.h"

Vector *GaussElimination(Matrix *A, Vector *b);
Vector *GaussEliminationWithPivoting(Matrix *A, Vector *b);