#include "polynomial.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>
#include <errno.h>

#ifndef NAN
# error "ERROR: NAN value is not supported on current C platform..."
#endif

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
	poly_print_vec(testpoly);
	putc('\n', stdout);

	printf("Testing poly_getcoeff():\n");
	for (size_t i = 0; i <= poly_getdegree(testpoly); ++i)
		printf("%g\n", poly_getcoeff(testpoly, i));

	printf("Computing testpoly(x) at x = %g\n", x_in);
	printf("testpoly(%g) = %g\n", x_in, polynomial_compute(testpoly, x_in));

	printf("Computing derivative of testpoly at x = %g\n", x_in);
	printf("testpoly'(%g) = %g\n", x_in, poly_comp_deriv(testpoly, x_in));

	printf("Resizing testpoly to 10th degree polynomial:\n");
	if (!poly_resize(testpoly, 10))
		fprintf(stderr, "p is invalid...\n");
	printf("testpoly is now %zuth degree and its elements are:\n", poly_getdegree(testpoly));
	poly_print_vec(testpoly);
	putc('\n', stdout);

	printf("Printing null poly:\n");
	poly_print_vec(0);
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

	printf("Generating polynomials from v and w.\n");
	polynomial* vpoly = poly_new(4, v);
	polynomial* wpoly = poly_new(4, w);

	printf("Polynomial v is: ");
	poly_print_vec(vpoly);
	putc('\n', stdout);
	printf("Polynomial w is: ");
	poly_print_vec(wpoly);
	putc('\n', stdout);

	printf("Adding v into w gives: ");
	poly_print_vec(poly_add(wpoly, vpoly));
	putc('\n', stdout);

	printf("Multipliying w by 3.14 gives: ");
	poly_print_vec(poly_mult(wpoly, 3.14));
	putc('\n', stdout);

	printf("Subtracting v from (1/3.14)w gives: ");
	poly_print_vec(poly_add(poly_mult(wpoly, 1.0/3.14), poly_mult(vpoly, -1)));
	putc('\n', stdout);

	printf("Resizing testpoly back to 2nd degree: ");
	poly_print_vec(poly_trim(testpoly, 1E-10));
	putc('\n', stdout);
#if 0
	printf("Subtracting v from testpoly gives: ");
	poly_print_vec(poly_add(testpoly, vpoly));
	putc('\n', stdout);
	
	polynomial* testfactor = poly_new(1, (double[2]) { 1, 1 });
	printf("Dividing testpoly by testfactor: ");
	poly_print_vec(testfactor);
	putc('\n', stdout);

	poly_div(testpoly, testfactor);
	printf("Result is: ");
	poly_print_vec(testpoly);
	putc('\n', stdout);
	poly_delete(testfactor);
#endif

	printf("Finding a root of testpoly at x = %g\n", x_in);
	printf("A root of testpoly is: %g\n", poly_findroot(testpoly, x_in));

	printf("Subtracting testpoly from itself gives: ");
	polynomial* testcpy = poly_copy(testpoly);
	poly_print_vec(poly_add(testpoly, poly_mult(testcpy, -1)));
	putc('\n', stdout);

	printf("Mulitplying v by 0 gives: ");
	poly_print_vec(poly_mult(vpoly, 0));
	putc('\n', stdout);

	poly_delete(testpoly);
	poly_delete(testcpy);
	poly_delete(vpoly);
	poly_delete(wpoly);
}
