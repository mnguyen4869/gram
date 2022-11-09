#include "matops.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

matrix *multiply(matrix* m1, matrix* m2)
{
	if (m1 -> num_cols == m2 -> num_rows) {
		matrix *m = create_mat(m1 -> num_rows, m2 -> num_cols);
		fill_mat(m, 0);
		unsigned int dim = m -> num_rows * m -> num_cols;
		// k = spots to fill in result
		for (unsigned int k = 0; k < dim; k++) { 
			double sum = 0;
			// i number of elements to look in each matrix
			for (unsigned int i = 0; i < m1 -> num_cols; i++) { 
				sum += m1 -> data[(k / m -> num_cols) * m1 -> num_cols + i]
					 * m2 -> data[(i * m2 -> num_cols) + k % m2 -> num_cols];
			}
			m -> data[k] = sum;
		}
		return m;
	}
	fprintf(stderr, "Dimensions of matrices are not valid m1 rows %d != m2 cols %d\n",
			m1 -> num_cols, m2 -> num_rows);
	exit(1);
}

matrix *add(matrix* m1, matrix* m2)
{
	if (m1 -> num_rows == m2 -> num_rows && m1 -> num_cols == m2 -> num_cols) {
		matrix *m = create_mat(m1 -> num_rows, m1 -> num_cols);
		unsigned int dim = m -> num_rows * m -> num_cols;
		for (int i = 0; i < dim; i++) {
			m -> data[i] = m1 -> data[i] + m2 -> data[i];
		}
		return m;
	} 
	fprintf(stderr, "Dimensions of given matrices are not equal\n");
	exit(1);
}

matrix *subtract(matrix* m1, matrix* m2)
{
	if (m1 -> num_rows == m2 -> num_rows && m1 -> num_cols == m2 -> num_cols) {
		matrix *m = create_mat(m1 -> num_rows, m1 -> num_cols);
		unsigned int dim = m -> num_rows * m -> num_cols;
		for (int i = 0; i < dim; i++) {
			m -> data[i] = m1 -> data[i] - m2 -> data[i];
		}
		return m;
	} 
	fprintf(stderr, "Dimensions of given matrices are not equal\n");
	exit(1);
}

matrix *apply(double (*func)(double), matrix* m)
{
	matrix *mat = copy_mat(m);
	unsigned int dim = mat -> num_rows * mat -> num_cols;
	for (int i = 0; i < dim; i++) {
			mat -> data[i] = (*func)(m -> data[i]);
	}
	return mat;
}
matrix *scale(double n, matrix* m) 
{
	matrix* mat = copy_mat(m);
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (int i = 0; i < dim; i++) {
		mat -> data[i] *= n;
	}
	return mat;
}

matrix *addScalar(double n, matrix* m)
{
	matrix* mat = copy_mat(m);
	unsigned int dim = m -> num_rows * m -> num_cols;
	for (int i = 0; i < dim; i++) {
		mat -> data[i] += n;
	}
	return mat;
}

matrix *transpose(matrix* m)
{
	matrix *mat = create_mat(m -> num_cols, m -> num_rows);
	for (int i = 0; i < m -> num_rows; i++) {
		for (int j = 0; j < m -> num_cols; j++) {
			mat -> data[j * m -> num_rows + i] = m -> data[i * m -> num_cols + j];
		}
	}
	return mat;
}
