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
#include <stdlib.h>
#include <stdio.h>

/* For complex.h */
#include <tgmath.h>
#include <float.h>

#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic.\n"
#endif

/* Uncomment this to enable DEBUG mode */
#define DEBUG

/* Make this as small as you need */
static double const h = 0x1P-24;

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
	double complex bi_difference = F(z + h) - F(z - h);
	return bi_difference / (2 * h);
}

int main(int argc, char* argv[argc+1]) {
	if (argc != 3) {
		printf("This program requires two arguments: the real and imaginary parts of your complex double input.\n");
		return EXIT_FAILURE;
	}

	double complex input = CMPLX(strtod(argv[1], 0), strtod(argv[2], 0));
#ifdef DEBUG
printf("Received input: %.5f + I*%.5f\n", creal(input), cimag(input));
#endif
	double complex result = f(F, input);
	printf("The derivative is: %.5f + I*%.5f\n", creal(result), cimag(result));

	return EXIT_SUCCESS;
}
