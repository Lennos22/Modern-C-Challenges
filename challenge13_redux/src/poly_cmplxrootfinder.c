/* Created by Nelson Cardona
 * Creation Date/Time: 10-04-23/23:21
 */
#ifdef __STDC_NO_COMPLEX__
# error "ERROR: current C platform does not support complex arithmetic..."
#endif
#include "polynomial.h"
#include "vector.h"
#include "math_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <tgmath.h>

int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		fprintf(stderr, "Program args: coefficients..., z_initial\n");
		fprintf(stderr, "coefficients... are the complex coefficients of polynomial: az^n "
				"+ bz^(n-1) + cz^(n-2) + ...\n");
		fprintf(stderr, "z_initial is the initial guess of one of the roots of the polynomial\n");

		return EXIT_FAILURE;
	}
	double complex coeff[argc-2];
	for (int i = 1; i < argc-1; ++i)
		coeff[argc-2-i] = strtocmplx(argv[i]);
	complex_polynomial* cpoly = cpoly_new(argc-3, coeff);
	if (!cpoly) {
		fprintf(stderr, "ERROR: failed to allocate memory for cpoly\n");
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}
	double complex z_init = strtocmplx(argv[argc-1]);
	printf("Finding roots of complex polynomial: ");
	cpoly_print_func(cpoly);
	putc('\n', stdout);
	printf("Using initial guess: ");
	print_cmplx(z_init);
	putc('\n', stdout);

	double complex roots[cpoly_getdegree(cpoly)];
	cpoly_getroots(cpoly, z_init, roots);

	printf("The roots are:\n");
	for (size_t i = 0; i < cpoly_getdegree(cpoly); ++i) {
		print_cmplx(roots[i]);
		if (i < cpoly_getdegree(cpoly)-1)
			printf(", ");
	}
	putc('\n', stdout);

	return EXIT_SUCCESS;
}
