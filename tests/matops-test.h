#ifndef MATOPS_TEST
#define MATOPS_TEST

#include "../src/matops.h"
#include "../src/matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool test_dot(void);

bool test_multiply(void);

bool test_add(void);

bool test_subtract(void);

bool test_apply(void);

bool test_scale(void);

bool test_add_scalar(void);

bool test_transpose(void);

#endif /* !MATOPS_TEST */
