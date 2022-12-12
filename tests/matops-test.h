#ifndef MATOPS_TEST
#define MATOPS_TEST

#include "../src/matops.h"
#include "../src/matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool test_multiply();

bool test_add();

bool test_subtract();

bool test_apply();

bool test_scale();

bool test_addScalar();

bool test_transpose();

#endif /* !MATOPS_TEST */
