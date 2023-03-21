/* Created by: Nelson Cardona
 * 
 * A more sensible algorithm that does away with the use of
 * minPrimeFactor(). Found this in GeeksforGeeks
 */
#include <stdlib.h>
#include <stdio.h>

/* Required for binary properties of floats */
#include <float.h>
/* Required for sqrt() */
#include <tgmath.h>

/* Defines safe-spot for sqrt() imprecision */
#define BOUND 1U

static size_t dbl_limit = 0;

/* This uses an approximation method that I developed, myself!
 * You can find it in "challenge9 doodles.xopp"
 */
size_t compLimit(size_t N) {
	long double a = floorl(sqrt(N));
	if ((long double) N - a*a > BOUND)
		a = ceill((N+a)/(a+1));

	return (size_t) a;
}

void factor(size_t N) {
	printf("%zu: ", N);
	if (!N) return;
	while (!(N % 2)) {
		printf("2 ");
		N /= 2;
	}

	size_t i = 3;
	size_t limit = (N < dbl_limit) ? sqrtl(N) : compLimit(N);
	while (i <= limit) {
		while (!(N % i)) {
			printf("%zu ", i);
			N /= i;
			limit = (N < dbl_limit) ? sqrtl(N) : compLimit(N);
		}
		i += 2;
	}

	if (N > 2)
		printf("%zu ", N);
	
	printf("\n");
}

int main(int argc, char* argv[argc+1]) {
	int digits = 0;
	if (sizeof(long double) <= sizeof(size_t))
		digits = LDBL_MANT_DIG;
	else if (sizeof(double) <= sizeof(size_t))
		digits = DBL_MANT_DIG;
	else if (sizeof(float) <= sizeof(size_t))
		digits = FLT_MANT_DIG;
	else {
		printf("ERROR: Somehow, integer types on this C platform don't fit on any floating-point types.\n");
		printf("You should probably get a new PC...\n");
		return EXIT_FAILURE;
	}
#if FLT_RADIX == 2
	dbl_limit = 1ULL << digits;
#else
	dbl_limit = powl(FLT_RADIX, digits);
#endif

	for (int i = 1; i < argc; ++i) {
		size_t n = strtoull(argv[i], 0, 0);

		factor(n);
	}

	return EXIT_SUCCESS;
}
