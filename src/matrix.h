#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	unsigned int num_rows;
	unsigned int num_cols;
	double *data; 
} matrix;

matrix *grm_create_mat(unsigned int row, unsigned int col);

void grm_copy_data(matrix *m, double *data, size_t size);

void grm_fill_mat(matrix *m, double n);

void grm_free_mat(matrix **m);

void grm_print_mat(matrix *m);

matrix *grm_copy_mat(matrix *m);

void grm_save_mat(matrix *m, char *filestr);

matrix *grm_load_mat(char *filestr);

int grm_argmax_mat(matrix *m);

matrix *grm_flatten_mat(matrix *m, int axis);

matrix *grm_create_rand_mat(unsigned int row, unsigned int col);

matrix *grm_create_idmat(unsigned int n);

matrix *grm_get_row(matrix *m, unsigned int i);

void grm_set_row(matrix *m, unsigned int i, double *d);

matrix *grm_get_col(matrix *m, unsigned int j);

void grm_set_col(matrix *m, unsigned int j, double *d);

#endif /* !MATRIX */
