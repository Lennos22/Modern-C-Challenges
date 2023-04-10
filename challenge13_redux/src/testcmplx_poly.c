/* Created by Nelson Cardona
 * Creation Date/Time: 10-04-23/17:23
 */
#ifdef __STDC_NO_COMPLEX__
# error "ERROR: current C platform does not support complex arithmetic..."
#endif
#include "polynomial.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

static double complex strtocmplx(char const str[static 1]);

int main(int argc, char* argv[argc+1]) {
	complex_polynomial* testpoly;
	if (argc < 2)
		testpoly = cpoly_new(0, 0);
	else {
		double complex coeff[argc-1];
		for (int i = 1; i < argc; ++i)
			coeff[argc-1-i] = strtocmplx(argv[i]);
		testpoly = cpoly_new(argc-2, coeff);
	}
	if (!testpoly)
		return EXIT_FAILURE;
	cpoly_print_func(testpoly);
	putc('\n', stdout);

	double complex v[] = {-1, 3-2*I, 10};
	double complex w[] = {19, -2.138*I, -2+6.24*I};
	printf("Vector v: ");
	cvector_print(3, v);
	putc('\n', stdout);
	printf("Vector w: ");
	cvector_print(3, w);
	putc('\n', stdout);

	complex_polynomial* vpoly = cpoly_new(2, v);
	complex_polynomial* wpoly = cpoly_new(2, w);
	printf("Polynomial v: ");
	cpoly_print_func(vpoly);
	putc('\n', stdout);
	printf("Polynomial w: ");
	cpoly_print_func(wpoly);
	putc('\n', stdout);

	printf("Adding testpoly to v gives: ");
	cpoly_print_func(cpoly_add(vpoly, testpoly));
	putc('\n', stdout);

	printf("Multiplying testpoly by 2.83i gives: ");
	cpoly_print_func(cpoly_mult(testpoly, 2.83*I));
	putc('\n', stdout);

	printf("Subtracting (1/2.83i)*testpoly to v gives: ");
	cpoly_print_func(cpoly_add(vpoly, cpoly_mult(testpoly, -1.0/(2.83*I))));
	putc('\n', stdout);

	cpoly_mult(testpoly, -1);

	printf("testpoly(10i) = %g + %gi\n", creal(complex_polynomial_compute(testpoly, 10*I)),
				cimag(complex_polynomial_compute(testpoly, 10*I)));
	printf("testpoly'(10i) = %g + %gi\n", creal(cpoly_comp_deriv(testpoly, 10*I)),
				cimag(cpoly_comp_deriv(testpoly, 10*I)));

	printf("One root of testpoly is: %g + %gi\n", creal(cpoly_findroot(testpoly, 10*I)),\
			cimag(cpoly_findroot(testpoly, 10*I)));

	cpoly_delete(testpoly);
	cpoly_delete(vpoly);
	cpoly_delete(wpoly);

	return EXIT_SUCCESS;
}

static double complex strtocmplx(char const start[static 1]) {
	double complex ret = 0.0;
	if (start) {
		char* end = 0;
		double real = strtod(start, &end);
#ifndef NDEBUG
		printf("end string is: %s\n", end);
#endif
		if (start == end) return ret;
		if (*end == 'i') return real*I;
		ret += real;
		start = end;
		double imag = strtod(start, &end);
#ifndef NDEBUG
		printf("imag is %g and end char is: %c\n", imag, *end);
#endif
		if (*end != 'i') return ret;
		ret += imag*I;
	}
#ifndef NDEBUG
	printf("Re(ret) = %g; Im(ret) = %g\n", creal(ret), cimag(ret));
#endif
	return ret;
}
