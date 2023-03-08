/* Created by: Nelson Cardona
 * Start Time/Date: 16:05/8-03-23
 * Completion Time/Date
 */
#include <stdlib.h>
#include <stdio.h>

/* For complex.h */
#include <tgmath.h>

#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic\n"
#endif

/* Put whatever complex differentiable function you want in here! */
double complex F(double complex z) {
	return csin(z);
}

/* Using two-sided differencing method. I can't really ensure the
 * pre-condition that the real and imaginary parts are partially
 * differentiably, but I think I can ensure the Cauchy-Riemann
 * eqns. are satisfied!
 */
double complex f(double complex F(double complex), double complex z) {
	return 0;
}

int main(int argc, char* argv[argc+1]) {
	return EXIT_SUCCESS;
}
