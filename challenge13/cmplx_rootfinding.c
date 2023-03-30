/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/20:29
 */
/**
  * @file cmplx_rootfinding.c
  * Finds a root of complex sin (or some other complex function
  * you set, here!) based on a user input z_initial value.
  */
#include "newton_raphson.h"
#include "complx_num_derivative.h"

#ifdef __STDC_NO_COMPLEX__
#error "Error: Current C platform does not support complex arithmetic..."
#endif

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

static const int dp_default = 3;
static const cmplx_diff_function* F = csin;

/**
  * Make ur own polynomial!
  */
double polynom_random(double x) {
	return (x-2)*(x-10)*(x+100.183592);
}

int main(int argc, char* argv[argc+1]) {
	if (argc < 3) {
		fprintf(stderr, "Program expects at least two arguments:\n");
		fprintf(stderr, "Re(z_initial) Im(z_initial) [dec_places]\n");
		return EXIT_FAILURE;
	}
	double complex z_in = strtod(argv[1], 0) + I*strtod(argv[2], 0);
	int num_dp = (argc >= 4) ? strtol(argv[3], 0, 0) : dp_default;
	double complex root = cmplx_newton_raphson(F, z_in, num_dp);

	printf("Root of sin(z) near z = %g + i*%g is x = %.*f + i*%.*f\n", creal(z_in), cimag(z_in), num_dp, creal(root), num_dp, cimag(root));

	return EXIT_SUCCESS;
}
