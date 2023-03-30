/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:21
 */
/**
  * @file realpolyroots.c
  * Computes the roots of a polynomial of any degree.
  *
  * @note I know, I use a global variable for my polynomial function, see polynomial.c. The precision isn't the best. You can tighten the
  * epsilon convergence value in newton_raphson.h, but you'll find that
  * many of the whole number roots will still output with a fractional
  * part. :(
  */
#include "polynomial.h"
#include "newton_raphson.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

double polynomial_func(double x);

static polynomial poly_in = { 0 };

int main(int argc, char* argv[argc+1]) {
	if (argc < 3) {
		fprintf(stderr, "Program requires arguments a, b, c, ... x_init coeffecients of polynomial ax^n + bx^(n-1) + cx^(n-2) + ... and initial guess\n");
		return EXIT_FAILURE;
	}
	double in_coeff[argc-2];
	for (int i = 1; i < argc-1; ++i) {
		in_coeff[argc-2-i] = strtod(argv[i], 0);
	}
	poly_in.degree = argc-3,
	poly_in.coeff = in_coeff,

	printf("Polynomial (degree %zu) input is:\n", poly_in.degree);
	poly_print(&poly_in);

	double x_initial = strtod(argv[argc-1], 0);
	double roots[poly_in.degree];
	size_t num_roots = poly_real_roots(polynomial_func, x_initial, &poly_in, roots);
	printf("There are %zu roots in poly_in\n", num_roots);
	for (size_t i = 0; i < num_roots; ++i)
		printf("%.3f, ", roots[i]);
	if (num_roots) printf("\n");

	return EXIT_SUCCESS;
}

double polynomial_func(double x) {
	double res = 0;
	
	for (size_t i = 0; i <= poly_in.degree; ++i)
		res += poly_in.coeff[i]*pow(x, i);

	return res;
}
