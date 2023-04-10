/* Created by Nelson Cardona
 * Creation Date/Time: 09-04-23/23:55
 */
/**
  * @file poly_rootfinder.c
  *
  * Computes all the *real* roots of a given polynomial.
  * 
  * Takes user input of list of doubles as arguments of program and generates a polynomial with the
  * zeroth coefficient being the first argument and subsequent arguments being subsequent
  * coefficients. The program then takes the polynomial and calculates all of its *real* roots and
  * outputs them in `stdout`.
  */
#include "polynomial.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		fprintf(stderr, "Program args:  coefficients..., x_initial\n");
		fprintf(stderr, "coefficients.. are the coefficients of polynomial: ax^n + bx^(n-1) + "
				"cx^(n-2) + ...\n");
		fprintf(stderr, "listed in the form: a, b, c, ...\n");
		fprintf(stderr, "x_initial is the initial guess of one of the roots of the polynomial\n");
		
		return EXIT_SUCCESS;
	}
	double usr_inp[argc-2];
	for (int i = 1; i < argc-1; ++i)
		usr_inp[argc-2-i] = strtod(argv[i], 0);
	polynomial* p = poly_new(argc-3, usr_inp);
	double x_init = strtod(argv[argc-1], 0);
	printf("Finding roots of polynomial: ");
	poly_print_func(p);
	putc('\n', stdout);
	printf("Using initial guess: %g\n", x_init);
	poly_printroots(p, x_init);
	poly_delete(p);

	return EXIT_SUCCESS;
}
