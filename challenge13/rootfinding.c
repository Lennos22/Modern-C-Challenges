/* Created by Nelson Cardona
 * Creation Date/Time: 29-03-23/23:23
 */
/**
  * @file rootfinding.c
  * Finds a root of sin (or some other function you set, here!)
  * based on a user input x_initial value.
  */
#include "newton_raphson.h"
#include "numerical_derivative.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

static const int dp_default = 3;
static const diff_function* F = sin;

/**
  * Make ur own polynomial!
  */
double polynom_random(double x) {
	return (x-2)*(x-10)*(x+100.183592);
}

int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		fprintf(stderr, "Program expects at least two arguments:\n");
		fprintf(stderr, "x_initial [dec_places]\n");
		return EXIT_FAILURE;
	}
	double x_in = strtod(argv[1], 0);
	int num_dp = (argc >= 3) ? strtol(argv[2], 0, 0) : dp_default;
	double root = newton_raphson(F, x_in, num_dp);

	printf("Root of sin(x) near %g is x = %.*f\n", x_in, num_dp, root);

	return EXIT_SUCCESS;
}
