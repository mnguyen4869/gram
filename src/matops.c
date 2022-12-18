#include "matops.h"

matrix *grm_dot(matrix *m1, matrix *m2)
{
	if (m1->num_cols == m2->num_rows) {
		matrix *m = grm_create_mat(m1->num_rows, m2->num_cols);
		grm_fill_mat(m, 0);
		size_t dim = m->num_rows * m->num_cols;
		// k = spots to fill in result
		for (size_t k = 0; k < dim; k++) { 
			double sum = 0;
			// i number of elements to look in each matrix
			for (size_t i = 0; i < m1->num_cols; i++) { 
				sum += m1->data[(k / m->num_cols) * m1->num_cols + i]
					 * m2->data[(i * m2->num_cols) + k % m2->num_cols];
			}
			m->data[k] = sum;
		}
		return m;
	}
	fprintf(stderr, "Dimensions are not valid m1 rows %ld != m2 cols %ld\n",
			m1->num_cols, m2->num_rows);
	return NULL;
}

matrix *grm_add(matrix *m1, matrix *m2)
{
	if (m1->num_rows == m2->num_rows && m1->num_cols == m2->num_cols) {
		matrix *m = grm_create_mat(m1->num_rows, m1->num_cols);
		size_t dim = m->num_rows * m->num_cols;
		for (size_t i = 0; i < dim; i++) {
			m->data[i] = m1->data[i] + m2->data[i];
		}
		return m;
	}
	fprintf(stderr, "Dimensions of given matrices are not equal\n");
	return NULL;
}

matrix *grm_subtract(matrix *m1, matrix *m2)
{
	if (m1->num_rows == m2->num_rows && m1->num_cols == m2->num_cols) {
		matrix *m = grm_create_mat(m1->num_rows, m1->num_cols);
		size_t dim = m->num_rows * m->num_cols;
		for (size_t i = 0; i < dim; i++) {
			m->data[i] = m1->data[i] - m2->data[i];
		}
		return m;
	}
	fprintf(stderr, "Dimensions of given matrices are not equal\n");
	return NULL;
}

matrix *grm_multiply(matrix *m1, matrix *m2)
{
	if (m1->num_rows == m2->num_rows && m1->num_cols == m2->num_cols) {
		matrix *m = grm_create_mat(m1->num_rows, m1->num_cols);
		size_t dim = m->num_rows * m->num_cols;
		for (size_t i = 0; i < dim; i++) {
			m->data[i] = m1->data[i] * m2->data[i];
		}
		return m;
	}
	fprintf(stderr, "Dimensions of given matrices are not equal\n");
	return NULL;
}

matrix *grm_apply(double (*func)(double), matrix *m)
{
	matrix *mat = grm_copy_mat(m);
	size_t dim = mat->num_rows * mat->num_cols;
	for (size_t i = 0; i < dim; i++) {
			mat->data[i] = (*func)(m->data[i]);
	}
	return mat;
}
matrix *grm_scale(double n, matrix *m) 
{
	matrix* mat = grm_copy_mat(m);
	size_t dim = m->num_rows * m->num_cols;
	for (size_t i = 0; i < dim; i++) {
		mat->data[i] *= n;
	}
	return mat;
}

matrix *grm_add_scalar(double n, matrix *m)
{
	matrix* mat = grm_copy_mat(m);
	size_t dim = m->num_rows * m->num_cols;
	for (size_t i = 0; i < dim; i++) {
		mat->data[i] += n;
	}
	return mat;
}

matrix *grm_transpose(matrix *m)
{
	matrix *mat = grm_create_mat(m->num_cols, m->num_rows);
	for (size_t i = 0; i < m->num_rows; i++) {
		for (size_t j = 0; j < m->num_cols; j++) {
			mat->data[j * m->num_rows + i] = m->data[i * m->num_cols + j];
		}
	}
	return mat;
}
