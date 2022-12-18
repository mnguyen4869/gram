#include "matrix.h"

#define MAXSIZE 150

matrix *grm_create_mat(size_t row, size_t col)
{
	if (row == 0 || col == 0) {
		fprintf(stderr, "Row and/or Column number is 0\n");
		return NULL;
	}
	matrix *m;
	if ((m = malloc(sizeof(*m))) == NULL) {
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
	size_t dim = m->num_rows * m->num_cols;
	if (size == dim) {
		for (size_t i = 0; i < dim; i++) {
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
	size_t dim = m->num_rows * m->num_cols;
	for (size_t i = 0; i < dim; i++) {
		if (i != 0 && i % m->num_cols == 0)
			printf("\n");
		printf("%1.6f ", m->data[i]);
	}
	printf("\n");
}

matrix *grm_copy_mat(matrix *m)
{
	size_t dim = m->num_rows * m->num_cols;
	matrix *mat = grm_create_mat(m->num_rows, m->num_cols);
	for (size_t i = 0; i < dim; i++) {
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
	fprintf(file, "%ld\n", m->num_rows);
	fprintf(file, "%ld\n", m->num_cols);
	size_t dim = m->num_rows * m->num_cols;
	for (size_t i = 0; i < dim; i++) {
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
	size_t rows = atoi(entry);
	fgets(entry, MAXSIZE, file);
	size_t cols = atoi(entry);
	matrix *m = grm_create_mat(rows, cols);
	size_t dim = rows * cols;
	for (size_t i = 0; i < dim; i++) {
		fgets(entry, MAXSIZE, file);
		m->data[i] = strtod(entry, NULL);
	}
	fclose(file);
	return m;
}

int grm_argmax_mat(matrix *m)
{
	int max = 0;
	size_t dim = m->num_rows * m->num_cols;
	for (size_t i = 1; i < dim; i++) {
		if (m->data[max] < m->data[i])
			max = i;
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

matrix *grm_create_rand_mat(size_t row, size_t col, double min, double max)
{
	matrix *m = grm_create_mat(row, col);
	size_t dim = m->num_rows * m->num_cols;
	double range = max - min;
	for (size_t i = 0; i < dim; i++) {
		// generate [0, 1]
		double rand_d = ((double) rand() / (double) ((unsigned) RAND_MAX + 1));
		m->data[i] = rand_d * range + min;
	}
	return m;
}

matrix *grm_create_idmat(size_t n)
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

matrix *grm_get_row(matrix *m, size_t i)
{
	if (i >= m->num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		return NULL;
	}
	matrix *frow = grm_create_mat(1, m->num_cols);
	i *= m->num_cols;
	for (size_t j = 0; j < m->num_cols; j++) {
		frow->data[j] = m->data[i + j];
	}
	return frow;
}

void grm_set_row(matrix *m, size_t i, double *d)
{
	if (i >= m->num_rows) {
		fprintf(stderr, "Row number out of bounds\n");
		exit(1);
	}
	i *= m->num_cols;
	for (size_t j = 0; j < m->num_cols; j++) {
		m->data[i++] = d[j];
	}
}

matrix *grm_get_col(matrix *m, size_t j)
{
	if (j >= m->num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	matrix *fcol = grm_create_mat(m->num_rows, 1);
	for (size_t i = 0; i < m->num_rows; i++) {
		fcol->data[i] = m->data[j];
		j += m->num_cols;
	}
	
	return fcol;
}

void grm_set_col(matrix *m, size_t j, double *d)
{
	if (j >= m->num_cols) {
		fprintf(stderr, "Column number out of bounds\n");
		exit(1);
	}
	for (size_t i = 0; i < m->num_rows; i++) {
		m->data[j] = d[i];
		j += m->num_cols;
	}
}
