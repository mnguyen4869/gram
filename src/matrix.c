#include "matrix.h"

#define MAXSIZE 150

matrix *grm_create_mat(unsigned int row, unsigned int col)
{
	if (row == 0 || col == 0) {
		fprintf(stderr, "Row and/or Column number is 0\n");
		return NULL;
	}
	matrix *m;
	if ((m = malloc(sizeof(matrix))) == NULL) {
		fprintf(stderr, "Malloc on matrix creation failed");
		return NULL;
	}
	m->num_rows = row;
	m->num_cols = col;
	if ((m->data = malloc((row * col) * sizeof(*(m->data)))) == NULL) {
		fprintf(stderr, "Malloc on matrix creation failed");
		free(m);
		return NULL;
	}
	return m;
}

void grm_copy_data(matrix *m, double *data, size_t size)
{
	unsigned int dim = m->num_rows * m->num_cols;
	if (size == dim) {
		for (unsigned int i = 0; i < dim; i++) {
			m->data[i] = data[i];
		}
	}
	else {
		fprintf(stderr, "Data's size does not match matrix");
	}
}

void grm_fill_mat(matrix *m, double n)
{
	unsigned int dim = m->num_rows * m->num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		m->data[i] = n;
	}
}

void grm_free_mat(matrix **m)
{
	free((*m)->data);
	free(*m);
	*m = NULL;
}

void grm_print_mat(matrix *m)
{
	unsigned int dim = m->num_rows * m->num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		if (i != 0 && i % m->num_cols == 0)
			printf("\n");
		printf("%1.3f ", m->data[i]);
	}
	printf("\n");
}

matrix *grm_copy_mat(matrix *m)
{
	unsigned int dim = m->num_rows * m->num_cols;
	matrix *mat = grm_create_mat(m->num_rows, m->num_cols);
	for (unsigned int i = 0; i < dim; i++) {
		mat->data[i] = m->data[i];
	}
	return mat;
}

void grm_save_mat(matrix *m, char *filestr)
{
	FILE *file = fopen(filestr, "w");
	if (file == NULL) {
		fprintf(stderr, "Opening file failed");
		return;
	}
	fprintf(file, "%d\n", m->num_rows);
	fprintf(file, "%d\n", m->num_cols);
	unsigned int dim = m->num_rows * m->num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		fprintf(file, "%.6f\n", m->data[i]);
	}
	fclose(file);
}

matrix *grm_load_mat(char *filestr)
{
	FILE *file = fopen(filestr, "r");
	if (file == NULL) {
		fprintf(stderr, "Opening file failed");
		return NULL;
	}
	char entry[MAXSIZE]; 
	fgets(entry, MAXSIZE, file);
	unsigned int rows = atoi(entry);
	fgets(entry, MAXSIZE, file);
	unsigned int cols = atoi(entry);
	matrix *m = grm_create_mat(rows, cols);
	unsigned int dim = rows * cols;
	for (unsigned int i = 0; i < dim; i++) {
		fgets(entry, MAXSIZE, file);
		m->data[i] = strtod(entry, NULL);
	}
	fclose(file);
	return m;
}

int grm_argmax_mat(matrix *m)
{
	double max = m->data[0];
	unsigned int dim = m->num_rows * m->num_cols;
	for (unsigned int i = 1; i < dim; i++) {
		if (max < m->data[i])
			max = m->data[i];
	}
	return max;
}

matrix *grm_flatten_mat(matrix *m, int axis)
{
	matrix *mat = grm_copy_mat(m);
	if (axis == 0) {
		mat->num_cols *= mat->num_rows;
		mat->num_rows = 1;
	}
	else {
		mat->num_rows *= mat->num_cols;
		mat->num_cols = 1;
	}
	return mat;
}

matrix *grm_create_rand_mat(unsigned int row, unsigned int col)
{
	matrix *m = grm_create_mat(row, col);
	unsigned int dim = m->num_rows * m->num_cols;
	for (unsigned int i = 0; i < dim; i++) {
		m->data[i] = ((double) rand() / (double) ((unsigned) RAND_MAX + 1));
	}
	return m;
}

matrix *grm_create_idmat(unsigned int n)
{
	matrix *m = grm_create_mat(n, n);
	int dim = n * n;
	int diag = 0;
	for (int i = 0; i < dim; i++) {
		if (i == diag) {
			m->data[i] = 1;
			diag += n + 1;
		}
		else {
			m->data[i] = 0;
		}
	}
	return m;
}

matrix *grm_get_row(matrix *m, unsigned int i)
{
	if (i >= m->num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		return NULL;
	}
	matrix *frow = grm_create_mat(1, m->num_cols);
	i *= m->num_cols;
	for (unsigned int j = 0; j < m->num_cols; j++) {
		frow->data[j] = m->data[i + j];
	}
	return frow;
}

void grm_set_row(matrix *m, unsigned int i, double *d)
{
	if (i >= m->num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		exit(1);
	}
	i *= m->num_cols;
	for (unsigned int j = 0; j < m->num_cols; j++) {
		m->data[i++] = d[j];
	}
}

matrix *grm_get_col(matrix *m, unsigned int j)
{
	if (j >= m->num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	matrix *fcol = grm_create_mat(m->num_rows, 1);
	for (unsigned int i = 0; i < m->num_rows; i++) {
		fcol->data[i] = m->data[j];
		j += m->num_cols;
	}
	
	return fcol;
}

void grm_set_col(matrix *m, unsigned int j, double *d)
{
	if (j >= m->num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	for (unsigned int i = 0; i < m->num_rows; i++) {
		m->data[j] = d[i];
		j += m->num_cols;
	}
}
