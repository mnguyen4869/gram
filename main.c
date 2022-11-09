#include "matrix.h"
#include "matops.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
	srand(time(0));
	// matrix *mat = create_mat(4, 3);
	// fill_mat(mat, 9);
	// print_mat(mat);
	// matrix *nat = copy_mat(mat);
	// free_mat(mat);
	// double d[4] = {1, 4, 5, 6};
	// double e[3] = {1, 4, 5};
	// set_row(nat, 2, d);
	// set_col(nat, 0, e);
	// printf("\n");
	// print_mat(nat);
	// matrix *a = load_mat("amat");
	matrix *a = create_rand_mat(3, 2);
	print_mat(a);
	// matrix *b = load_mat("bmat");
	// print_mat(b);
	matrix *c = transpose(a);
	print_mat(c);
	return 0;
}
