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

#define NDEBUG

#include <stdio.h>

/* For complex.h */
#include <tgmath.h>
#include <assert.h>

/* Honestly, I can't tell you how random some values can be.
 * If I calculate derivative of sin(z) at z = 10 + 10i,
 * then 0x1P-32 gives a perfect 0 for CR check. However,
 * when z = pi + i*pi, then the CR check is > 1. If I change
 * h_eps to 0x1P-48, then CR check for pi + i*p is a perfect
 * 0, but it becomes absurdly large for 10 + 10i. *shrugs*.
 * You just can't win...
 */
/* Make this as small as you need */
static double const h_eps = 0x1P-32;
static double const cr_eps = 0x1P-16;		// For Cauchy-Riemann check

/* Using two-sided differencing method. I can't really ensure the
 * pre-condition that the real and imaginary parts are partially
 * differentiable, but I think I can ensure the Cauchy-Riemann
 * eqns. are satisfied!
 */
double complex cmplx_f(cmplx_diff_function* F, double complex z) {
	double complex bi_diff_h = F(z + h_eps) - F(z - h_eps);
	double complex bi_diff_Ih = F(z + I*h_eps) - F(z - I*h_eps);
	double complex res_h = bi_diff_h / (2*h_eps);
	double complex res_Ih = bi_diff_Ih / (2*I*h_eps);

	if (cabs(res_h - res_Ih) >= cr_eps)
		fprintf(stderr, "Warning, Cauchy-Riemann check is too high @ %g + i%g. Result will be unstable.\n", creal(z), cimag(z));
assert(cabs(res_h - res_Ih) < cr_eps);

	return res_h;
}
