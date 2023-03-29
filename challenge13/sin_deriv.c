/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/17:08
 */
/**
  * @file sin_deriv.c
  * Takes user input x and calculates the derivative of sin(x).
  */ 
#include "numerical_derivative.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

static diff_function* F = sin;

int main(int argc, char* argv[argc+1]) {
	for (int i = 1; i < argc; ++i) {
		double in = strtod(argv[i], 0);

		printf("d/dx(sin(%g)) = %g\n", in, f(F, in));
	}

	return EXIT_SUCCESS;
}
