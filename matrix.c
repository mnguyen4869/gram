#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 150

matrix *create_mat(unsigned int row, unsigned int col)
{
	if (row == 0 || col == 0) {
		fprintf(stderr, "Row and/or Column number is 0\n");
	}
	matrix *m;
	if ((m = malloc(sizeof(matrix))) == NULL) {
		fprintf(stderr, "Malloc on matrix creation failed");
	}
	m -> num_rows = row;
	m -> num_cols = col;
	if ((m -> data = malloc((row * col) * sizeof(double))) == NULL) {
		fprintf(stderr, "Malloc on matrix creation failed");
	}
	return m;
}

void fill_mat(matrix *m, double n)
{
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		m -> data[i] = n;
	}
}

void free_mat(matrix *m)
{
	free(m -> data);
	free(m);
	m = NULL;
}

void print_mat(matrix *m)
{
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		if (i != 0 && i % m -> num_cols == 0)
			printf("\n");
		printf("%1.3f ", m -> data[i]);
	}
	printf("\n");
}

matrix *copy_mat(matrix *m)
{
	unsigned int dim = m -> num_rows * m -> num_cols;
	matrix *mat = create_mat(m -> num_rows, m -> num_cols);
	for (unsigned int i = 0; i < dim; i++) {
		mat -> data[i] = m -> data[i];
	}
	return mat;
}

void save_mat(matrix *m, char *filestr)
{
	FILE *file = fopen(filestr, "w");
	fprintf(file, "%d\n", m -> num_rows);
	fprintf(file, "%d\n", m -> num_cols);
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		fprintf(file, "%.6f\n", m -> data[i]);
	}
	fclose(file);
}

matrix *load_mat(char *filestr)
{
	FILE *file = fopen(filestr, "r");
	char entry[MAXSIZE]; 
	fgets(entry, MAXSIZE, file);
	unsigned int rows = atoi(entry);
	fgets(entry, MAXSIZE, file);
	unsigned int cols = atoi(entry);
	matrix *m = create_mat(rows, cols);
	unsigned int dim = rows * cols;
	for (unsigned int i = 0; i < dim; i++) {
		fgets(entry, MAXSIZE, file);
		m -> data[i] = strtod(entry, NULL);
	}
	fclose(file);
	return m;
}

int argmax_mat(matrix *m)
{
	double max = m -> data[0];
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (unsigned int i = 1; i < dim; i++) {
		if (max < m -> data[i])
			max = m -> data[i];
	}
	return max;
}

matrix *flatten_mat(matrix *m, int axis)
{
	matrix *mat = copy_mat(m);
	if (axis == 0) {
		mat -> num_cols *= mat -> num_rows;
		mat -> num_rows = 1;
	}
	else {
		mat -> num_rows *= mat -> num_cols;
		mat -> num_cols = 1;
	}
	return mat;
}

matrix *create_rand_mat(unsigned int row, unsigned int col)
{
	matrix *m = create_mat(row, col);
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		m -> data[i] = ((double) rand() / (double) ((unsigned) RAND_MAX + 1));
	}
	return m;
}

matrix *create_idmat(unsigned int n)
{
	matrix *m = create_mat(n, n);
	int dim = n * n;
	int diag = 0;
	for (int i = 0; i < dim; i++) {
		if (i == diag) {
			m -> data[i] = 1;
			diag += n + 1;
		}
		else {
			m -> data[i] = 0;
		}
	}
	return m;
}

double *get_row(matrix *m, unsigned int i)
{
	if (i >= m -> num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		exit(1);
	}
	double *frow;
	if ((frow = malloc(m -> num_cols * sizeof(double))) == NULL) {
		fprintf(stderr, "Getting malloc row failed ");
	}
	i *= m -> num_cols;
	for (unsigned int j = 0; j < m -> num_cols; j++) {
		frow[j] = m -> data[i];
	}
	return frow;
}

void set_row(matrix *m, unsigned int i, double *d)
{
	if (i >= m -> num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		exit(1);
	}
	i *= m -> num_cols;
	for (unsigned int j = 0; j < m -> num_cols; j++) {
		m -> data[i++] = d[j];
	}
}

double *get_col(matrix *m, unsigned int j)
{
	if (j >= m -> num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	double *frow;
	if ((frow = malloc(m -> num_rows * sizeof(double))) == NULL) {
		fprintf(stderr, "Getting malloc column failed");
	}
	for (unsigned int i = 0; i < m -> num_rows; i++) {
		frow[i] = m -> data[j];
		j += i * m -> num_cols;
	}
	return frow;
}

void set_col(matrix *m, unsigned int j, double *d)
{
	if (j >= m -> num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	for (unsigned int i = 0; i < m -> num_rows; i++) {
		m -> data[j] = d[i];
		j += i * m -> num_cols;
	}
}
