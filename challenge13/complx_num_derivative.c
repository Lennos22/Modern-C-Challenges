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

/* For complex.h */
#include <tgmath.h>
#include <float.h>
#include <assert.h>

/* Make this as small as you need */
static double const h_eps = 0x1P-32;
static double const cr_eps = 0x1P-24;		// For Cauchy-Riemann check

/* Using two-sided differencing method. I can't really ensure the
 * pre-condition that the real and imaginary parts are partially
 * differentiable, but I think I can ensure the Cauchy-Riemann
 * eqns. are satisfied!
 */
double complex f(cmplx_diff_function* F, double complex z) {
	double complex bi_difference = F(z + h_eps) - F(z - h_eps);

	double complex bi_diff_imag = F(z + I*h_eps) - F(z - I*h_eps);
	double complex cauchy_riemann = bi_difference - bi_diff_imag;
assert(cabs(cauchy_riemann) < cr_eps);

	
	return bi_difference / (2 * h_eps);
}
