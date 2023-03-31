/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/23:23
 */
/**
  * @file cmplxpolyroots.c
  * Computes ALL the complex roots of a complex polynomial.
  *
  * Takes user input to generate a polynomial and an initial guess
  * to compute every root.
  */
#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic..."
#endif

#include "polynomial.h"
#include "newton_raphson.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

double complex cmplx_polynomial_func(double complex z);

static cmplx_polynomial cmplx_poly_in = { 0 };

int main(int argc, char* argv[argc+1]) {
	if (argc < 3) {
		fprintf(stderr, "Program requires arguments a, b, c, ... x_init coeffecients of polynomial ax^n + bx^(n-1) + cx^(n-2) + ... and initial guess\n");
		return EXIT_FAILURE;
	}
	double complex in_coeff[argc-2];
	for (int i = 1; i < argc-1; ++i) {
		double re_coeff = 0;
		double im_coeff = 0;

		sscanf(argv[i], "%lf+i*%lf", &re_coeff, &im_coeff);
		sscanf(argv[i], "i*%lf\n", &im_coeff); 
		in_coeff[argc-2-i] = CMPLX(re_coeff, im_coeff);
	}
	cmplx_poly_in.degree = argc-3,
	cmplx_poly_in.coeff = in_coeff,

	printf("Polynomial (degree %zu) input is:\n", cmplx_poly_in.degree);
	cmplx_poly_print(&cmplx_poly_in);

	double complex z_initial = strtod(argv[argc-1], 0);
	double complex roots[cmplx_poly_in.degree];
	size_t num_roots = poly_cmplx_roots(cmplx_polynomial_func, z_initial, &cmplx_poly_in, roots);

	printf("There are %zu roots in your polynomial:\n", num_roots);
	for (size_t i = 0; i < num_roots; ++i)
		printf("%.4f+i*%.4f, ", creal(roots[i]), cimag(roots[i]));
	if (num_roots) printf("\n");

	return EXIT_SUCCESS;
}

double complex cmplx_polynomial_func(double complex z) {
	double complex res = 0;
	
	for (size_t i = 0; i <= cmplx_poly_in.degree; ++i)
		res += cmplx_poly_in.coeff[i]*cpow(z, i);

	return res;
}
