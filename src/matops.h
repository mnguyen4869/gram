#ifndef MATOPS
#define MATOPS

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

matrix *grm_multiply(matrix* m1, matrix* m2);

matrix *grm_add(matrix* m1, matrix* m2);

matrix *grm_subtract(matrix* m1, matrix* m2);

matrix *grm_apply(double (*func)(double), matrix* m);

matrix *grm_scale(double n, matrix* m);

matrix *grm_addScalar(double n, matrix* m);

matrix *grm_transpose(matrix* m);

#endif /* !MATOPS */
