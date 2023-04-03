#include "polynomial.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[argc+1]) {
	if (argc != 2) {
		fprintf(stderr, "Program requires one double argument\n");
		return EXIT_FAILURE;
	}
	double x_in = strtod(argv[1], 0);
	polynomial* testpoly = poly_new(2, (double[3]) {1, 2, 1});
	if (!testpoly) {
		fprintf(stderr, "Failed to initialize testpoly.\n");
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	printf("Initialized testpoly with degree %zu\n", poly_getdegree(testpoly));

	printf("testpoly elements are:\n");
	poly_print(testpoly);
	putc('\n', stdout);

	printf("Testing poly_getcoeff():\n");
	for (size_t i = 0; i <= poly_getdegree(testpoly); ++i)
		printf("%g\n", poly_getcoeff(testpoly, i));

	printf("Computing testpoly(x) at x = %g\n", x_in);
	printf("testpoly(%g) = %g\n", x_in, polynomial_compute(testpoly, x_in));
	poly_delete(testpoly);

	printf("Printing null poly:\n");
	poly_print(0);
	putc('\n', stdout);

	double v[5] = {3.2, -20, .999, 1, 0};
	double w[5] = {9, 8.2, 11.333, -69, 100029};

	printf("Using vectors v: ");
	vector_print(5, v);
	printf(" and w: ");
	vector_print(5, w);
	putc('\n', stdout);

	printf("Their sum is:\n");
	vector_print(5, vector_add(5, v, w));
	putc('\n', stdout);

	printf("5w is: ");
	vector_print(5, vector_mult(5, w, 5));
	putc('\n', stdout);

	printf("-(1/5)w is: ");
	vector_print(5, vector_mult(5, w, -0.2));
	putc('\n', stdout);

	printf("v+w = ");
	vector_print(5, vector_add(5, v, w));
	putc('\n', stdout);

	printf("Dot product of v and w is: %g\n", vector_dotproduct(5, v, vector_mult(5, w, -1)));
}
