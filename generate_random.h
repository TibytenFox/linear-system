#pragma once
#include <time.h>
#include "matrix.h"
#include "vector.h"

time_t GenerateRandomSeed();
Vector *GenerateVector(int size);
Matrix *GenerateMatrix(int rows, int cols);