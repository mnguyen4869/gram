#ifndef MATRIX_TEST
#define MATRIX_TEST

#include "../src/matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool test_fill_mat(void);

bool test_free_mat(void);

bool test_copy_mat(void);

bool test_save_load_mat(void);

bool test_argmax_mat(void);

bool test_flatten_mat(void);

bool test_create_rand_mat(void);

bool test_create_idmat(void);

bool test_get_row(void);

bool test_set_row(void);

bool test_get_col(void);

bool test_set_col(void);

#endif /* !MATRIX_TEST */
