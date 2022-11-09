#pragma once

typedef struct {
	unsigned int num_rows;
	unsigned int num_cols;
	double *data; 
} matrix;

matrix *create_mat(unsigned int row, unsigned int col);

void fill_mat(matrix *m, double n);

void free_mat(matrix *m);

void print_mat(matrix *m);

matrix *copy_mat(matrix *m);

void save_mat(matrix *m, char *filestr);

matrix *load_mat(char *filestr);

int argmax_mat(matrix *m);

matrix *flatten_mat(matrix *m, int axis);

matrix *create_rand_mat(unsigned int row, unsigned int col);

matrix *create_idmat(unsigned int n);

double *get_row(matrix *m, unsigned int i);

void set_row(matrix *m, unsigned int i, double *d);

double *get_col(matrix *m, unsigned int j);

void set_col(matrix *m, unsigned int j, double *d);
