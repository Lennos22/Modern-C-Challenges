/* TU adapted from code in Challenge 5
 * Creation Date/Time: 28-03-23/17:01
 */

/* Created by: Nelson Cardona
 * Start Time/Date: 16:05/8-03-23
 * Completion Time/Date: 20:39/8-03-23
 * Seems like the derivative is accurate to AT LEAST 5 d.p.
 * At least for sin(z).
 * NOTE: The c99 standard does not define COMPLX(). The clang
 * compiler on my laptop doesn't seem to compile it even with
 * -std=c11 so I had to use the gcc compiler for this
 * program
 */
#include "complx_num_derivative.h"

#include <stdlib.h>
#include <stdio.h>

/* For complex.h */
#include <tgmath.h>
#include <float.h>

/* Uncomment this to enable DEBUG mode */
#define DEBUG

/* Make this as small as you need */
static double const h = 0x1P-32;
#ifdef DEBUG
static double const eps = 0x1P-24;
#endif

/* Using two-sided differencing method. I can't really ensure the
 * pre-condition that the real and imaginary parts are partially
 * differentiable, but I think I can ensure the Cauchy-Riemann
 * eqns. are satisfied!
 */
double complex f(double complex F(double complex), double complex z) {
	double complex bi_difference = F(z + h) - F(z - h);
#ifdef DEBUG
printf("h interval is: %.3e\n", h);
double complex bi_diff_imag = F(z + I*h) - F(z - I*h);
double complex cauchy_riemann = bi_difference - bi_diff_imag;
printf("Cauchy-Riemann check using eps = %.3e\n", eps);
if (cabs(cauchy_riemann) < 0x1P-24)
		printf("Function is complex differentiable @ %.3f + I*%.3f\n", creal(z), cimag(z));
else {
		printf("Function is not complex differentiable @ %.3f + I*%.3f. Exiting program...\n", creal(z), cimag(z));
		return EXIT_FAILURE;
}
#endif
	return bi_difference / (2 * h);
}
