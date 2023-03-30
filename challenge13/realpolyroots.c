/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:21
 */
#include "polynomial.h"
#include "newton_raphson.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

double polynomial_func(double x);

static polynomial poly_in = { 0 };

int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		fprintf(stderr, "Program requires arguments a, b, c, ... coeffecients of polynomial ax^n + bx^(n-1) + cx^(n-2) + ...\n");
		return EXIT_FAILURE;
	}
	double in_coeff[argc-1];
	for (int i = 1; i < argc; ++i) {
		in_coeff[argc-1-i] = strtod(argv[i], 0);
	}
	poly_in.degree = argc-2,
	poly_in.coeff = in_coeff,

	printf("Polynomial (degree %zu) input is:\n", poly_in.degree);
	poly_print(&poly_in);

	polynomial test = {
		.degree = 1,
		.coeff = (double[2]) {
			[1] = 1,
			[0] = 2,
		},
	};
	if (poly_divnr(&poly_in, &test))
		printf("There is no remainder!\n");
	else
		printf("There is a remainder!\n");
	printf("Quotient (now degree %zu) is:\n", poly_in.degree);
	poly_print(&poly_in);

	return EXIT_SUCCESS;
}

double polynomial_func(double x) {
	double res = 0;
	
	for (size_t i = 0; i <= poly_in.degree; ++i)
		res += poly_in.coeff[i]*pow(x, i);

	return res;
}
