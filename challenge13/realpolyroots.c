/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:21
 */
#include "polynomial.h"
#include "newton_raphson.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		fprintf(stderr, "Program requires arguments a, b, c, ... coeffecients of polynomial ax^n + bx^(n-1) + cx^(n-2) + ...\n");
		return EXIT_FAILURE;
	}
	double in_coeff[argc-1];
	for (int i = 1; i < argc; ++i) {
		in_coeff[argc-1-i] = strtod(argv[i], 0);
	}
	polynomial poly_in = {
		.degree = argc-2,
		.coeff = in_coeff,
	};
	printf("Polynomial input is:\n");
	poly_print(&poly_in);

	return EXIT_SUCCESS;
}
