/* Created by Nelson Cardona
 * Creation Date/Time: 29-03-23/16:30
 */
#include "complx_num_derivative.h"

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

static cmplx_diff_function* F = csin;

int main(int argc, char* argv[argc+1]) {
	if (argc != 3) {
		fprintf(stderr, "Program requires two arguments: the real and imaginary parts of a complex number...\n");
		return EXIT_FAILURE;
	}
	double complex in = strtod(argv[1], 0) + I*strtod(argv[2], 0);
	double complex res = cmplx_f(F, in);

	printf("d/dx(sin(%g + i*%g)) = %g + i*%g\n", creal(in), cimag(in), creal(res), cimag(res));

	return EXIT_SUCCESS;
}
