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
static double const cr_eps = 0x1P-32;		// For Cauchy-Riemann check

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

assert(cabs(res_h - res_Ih) < cr_eps);

	return res_h;
}
