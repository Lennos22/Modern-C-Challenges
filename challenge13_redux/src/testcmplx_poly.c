/* Created by Nelson Cardona
 * Creation Date/Time: 10-04-23/17:23
 */
#ifdef __STDC_NO_COMPLEX__
# error "ERROR: current C platform does not support complex arithmetic..."
#endif
#include "polynomial.h"
#include "vector.h"
#include "math_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

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
	cpoly_print_vec(testpoly);
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

	printf("testpoly(10i) = ");
	print_cmplx(complex_polynomial_compute(testpoly, 10*I));
	putc('\n', stdout);
	printf("testpoly'(10i) = ");
	print_cmplx(cpoly_comp_deriv(testpoly, 10*I));
	putc('\n', stdout);

	printf("One root of testpoly is: ");
	print_cmplx(cpoly_findroot(testpoly, 10*I));
	putc('\n', stdout);

	printf("Copying v, w and testpoly\n");
	complex_polynomial* vcpy = cpoly_copy(vpoly);
	complex_polynomial* wcpy = cpoly_copy(wpoly);
	complex_polynomial* testcpy = cpoly_copy(testpoly);

	printf("v copy is: ");
	cpoly_print_vec(vcpy);
	putc('\n', stdout);
	printf("w copy is: ");
	cpoly_print_vec(wcpy);
	putc('\n', stdout);
	printf("testpoly copy is: ");
	cpoly_print_vec(testcpy);
	putc('\n', stdout);

	cpoly_delete(testpoly);
	cpoly_delete(vpoly);
	cpoly_delete(wpoly);
	cpoly_delete(vcpy);
	cpoly_delete(wcpy);
	cpoly_delete(testcpy);

	return EXIT_SUCCESS;
}
