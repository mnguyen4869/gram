#include "matrix-test.h"

bool test_fill_mat(void)
{
	matrix *m = grm_create_mat(10, 10);
	grm_fill_mat(m, 1.0);
	unsigned int dim = m->num_cols * m->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (m->data[i] != 1.0){
			return false;
		}
	}
	grm_free_mat(&m);
	return true;
}

bool test_free_mat(void)
{
	matrix *m = grm_create_mat(10, 10);
	grm_free_mat(&m);
	return (m == NULL);
}

bool test_copy_mat(void)
{
	matrix *m = grm_create_mat(10, 10);
	grm_fill_mat(m, 1.0);
	matrix *n = grm_copy_mat(m);
	grm_free_mat(&m);
	unsigned int dim = n->num_cols * n->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != 1.0){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}

bool test_save_load_mat(void)
{
	double data[10] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
	matrix *m = grm_create_mat(2, 5);
	unsigned int m_num_rows = m->num_rows;
	unsigned int m_num_cols = m->num_cols;
	grm_copy_data(m, data, 10);
	grm_save_mat(m, "tests/test_matrix");
	grm_free_mat(&m);
	matrix *n = grm_load_mat("tests/test_matrix");
	unsigned int dim = n->num_cols * n->num_rows;
	if (m_num_rows != n->num_rows && m_num_cols != n->num_cols) {
		return false;
	}
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != data[i]){
			return false;
		}
	}
	grm_free_mat(&n);
	return true;
}

bool test_argmax_mat(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	double max = grm_argmax_mat(m);
	grm_free_mat(&m);
	return (max == 9);
}

bool test_flatten_mat(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	matrix *n = grm_flatten_mat(m, 0);
	matrix *o = grm_flatten_mat(m, 1);
	grm_free_mat(&m);
	unsigned int n_num_rows = n->num_rows;
	unsigned int n_num_cols = n->num_cols;
	unsigned int o_num_rows = o->num_rows;
	unsigned int o_num_cols = o->num_cols;
	grm_free_mat(&n);
	grm_free_mat(&o);
	if (n_num_rows != 1 && n_num_cols != 10) {
		return false;
	}
	if (o_num_rows != 10 && o_num_cols != 1) {
		return false;
	}
	return true;
}

bool test_create_rand_mat(void)
{
	matrix *m = grm_create_rand_mat(5, 5, -1, 1);
	matrix *n = grm_create_rand_mat(5, 5, -1, 1);
	unsigned int dim = m->num_cols * m->num_rows;
	for (unsigned int i = 0; i < dim; i++) {
		if (n->data[i] != m->data[i]){
			grm_free_mat(&m);
			grm_free_mat(&n);
			return true;
		}
	}
	return false;
}

bool test_create_idmat(void)
{
	matrix *m = grm_create_idmat(5);
	for (unsigned int i = 0; i < m->num_rows; i++) {
		for (unsigned int j = 0; j < m->num_cols; j++) {
			if (i == j && m->data[i * m->num_rows + j] != 1) {
				return false;
			}
			if (i != j && m->data[i * m->num_rows + j] != 0) {
				return false;
			}
		}
	}
	grm_free_mat(&m);
	return true;
}

bool test_get_row(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	matrix *r = grm_get_row(m, 2);
	double er[2] = {5, 6};
	for (unsigned int i = 0; i < 2; i++) {
		if (r->data[i] != er[i]) {
			return false;
		}
	}
	grm_free_mat(&r);
	grm_free_mat(&m);
	return true;
}

bool test_set_row(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	double r[2] = {0, 7};
	grm_set_row(m, 2, r);
	for (unsigned int i = 0; i < 2; i++) {
		if (m->data[m->num_cols * 2 + i] != r[i]) {
			return false;
		}
	}
	grm_free_mat(&m);
	return true;
}

bool test_get_col(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	matrix *c = grm_get_col(m, 0);
	double ec[5] = {1, 3, 5, 7, 9};
	for (unsigned int i = 0; i < 5; i++) {
		if (c->data[i] != ec[i]) {
			return false;
		}
	}
	grm_free_mat(&c);
	grm_free_mat(&m);
	return true;
}

bool test_set_col(void)
{
	double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	matrix *m = grm_create_mat(5, 2);
	grm_copy_data(m, data, 10);
	double c[5] = {0, 0, 0, 0, 0};
	grm_set_col(m, 0, c);
	for (unsigned int i = 0; i < 5; i++) {
		if (m->data[i * m->num_cols] != c[i]) {
			return false;
		}
	}
	grm_free_mat(&m);
	return true;
}
