#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix-test.h"
#include "matops-test.h"

// int main (int argc, char *argv[])
int main ()
{
	srand(time(0)); // random seed for rand_mat

	// matrix tests

	assert(test_fill_mat());

	assert(test_free_mat());

	assert(test_copy_mat());

	assert(test_save_load_mat());
	
	assert(test_argmax_mat());

	assert(test_flatten_mat());

	assert(test_create_rand_mat());

	assert(test_create_idmat());

	assert(test_get_row());

	assert(test_set_row());

	assert(test_get_col());

	assert(test_set_col());

	// matrix operations test

	printf("All matrix tests pass\n");

	// printf("All matrix function tests pass");

	return 0;
}
