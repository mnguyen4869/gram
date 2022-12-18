#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	size_t num_rows;
	size_t num_cols;
	double *data; 
} matrix;

matrix *grm_create_mat(size_t row, size_t col);

void grm_copy_data(matrix *m, double *data, size_t size);

void grm_fill_mat(matrix *m, double n);

void grm_free_mat(matrix **m);

void grm_print_mat(matrix *m);

matrix *grm_copy_mat(matrix *m);

void grm_save_mat(matrix *m, char *filestr);

matrix *grm_load_mat(char *filestr);

int grm_argmax_mat(matrix *m);

matrix *grm_flatten_mat(matrix *m, int axis);

matrix *grm_create_rand_mat(size_t row, size_t col, double min, double max);

matrix *grm_create_idmat(size_t n);

matrix *grm_get_row(matrix *m, size_t i);

void grm_set_row(matrix *m, size_t i, double *d);

matrix *grm_get_col(matrix *m, size_t j);

void grm_set_col(matrix *m, size_t j, double *d);

#endif /* !MATRIX */
