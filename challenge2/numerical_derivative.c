/* Created by: Nelson Cardona
 * Start Time/Date: 11:39/5-03-23
 * Completion Time/Date: 13:21/5-03/23
 * NOTE: this algorithm is, by no means, perfect. It uses a two-sided
 * differencing method known as "centred differencing" which means
 * that it samples values around an epsilon interval. If your
 * function happens to be non-differentiable within that interval,
 * well... good luck...
 */
#include <stdlib.h>
#include <stdio.h>

/* For your bog standard differentiable functions (sin(), exp(), etc.) */
#include <tgmath.h>

/* You can make this as small as you want! */
static double const eps = 0x1P-16;

/* Function you want to differentiate. Feel free to use the
 * functions in tgmath.h. Or, make your own!
 */
double F(double x) {
		return sqrt(x);
}

/* Using a two-sided differencing method */
double f(double F(double), double x) {
		return (F(x + eps) - F(x - eps)) / (2 * eps);
}

int main(int argc, char* argv[argc+1]) {
		if (argc > 2) {
				printf("This program only takes one double argument.\n");
				return EXIT_FAILURE;
		}
		double input = strtod(argv[1], 0);

		printf("The derivate of F at x = %s is %.5f!\n", argv[1], f(F, input));

		return EXIT_SUCCESS;
}
