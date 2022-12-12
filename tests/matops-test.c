#include "matops-test.h"

// to test apply
double ReLU (double in) {
	if (in > 0) {
		return in;
	}
	return 0;
}

bool test_multiply()
{
	double m_data[10] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	double n_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *n = grm_create_mat(5, 2);
	grm_copy_data(n, n_data, 10);

	matrix *o = grm_multiply(m, n);
	grm_free_mat(&m);
	grm_free_mat(&n);

	if (o->num_rows != 2 && o->num_cols != 2) {
		return false;
	}
	double expected[4] = {25, 30, 50, 60};
	unsigned int dim = o->num_cols * o->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (o->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&o);
	return true;
}

bool test_add()
{
	double m_data[10] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	double n_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *n = grm_create_mat(2, 5);
	grm_copy_data(n, n_data, 10);

	matrix *o = grm_add(m, n);
	grm_free_mat(&m);
	grm_free_mat(&n);

	double expected[10] = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12};
	unsigned int dim = o->num_cols * o->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (o->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&o);
	return true;
}

bool test_subtract()
{
	double m_data[10] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	double n_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *n = grm_create_mat(2, 5);
	grm_copy_data(n, n_data, 10);

	matrix *o = grm_subtract(m, n);
	grm_free_mat(&m);
	grm_free_mat(&n);

	double expected[10] = {0, -1, -2, -3, -4, -4, -5, -6, -7, -8};
	unsigned int dim = o->num_cols * o->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (o->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&o);
	return true;
}

bool test_apply()
{
	double m_data[10] = {-1, -1, -1, -1, -1, 2, 2, 2, 2, 2};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	matrix *n = grm_apply(ReLU, m);
	grm_free_mat(&m);

	double expected[10] = {0, 0, 0, 0, 0, 2, 2, 2, 2, 2};
	unsigned int dim = n->num_cols * n->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}

bool test_scale()
{
	double m_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	matrix *n = grm_scale(2, m);
	grm_free_mat(&m);

	double expected[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	unsigned int dim = n->num_cols * n->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}

bool test_addScalar()
{
	double m_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	matrix *n = grm_addScalar(2, m);
	grm_free_mat(&m);

	double expected[10] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	unsigned int dim = n->num_cols * n->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}

bool test_transpose()
{
	double m_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(2, 5);
	grm_copy_data(m, m_data, 10);

	matrix *n = grm_transpose(m);
	grm_free_mat(&m);

	if (n->num_rows != 5 && n->num_cols != 2) {
		return false;
	}

	double expected[10] = {1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
	unsigned int dim = n->num_cols * n->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != expected[i]){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}
