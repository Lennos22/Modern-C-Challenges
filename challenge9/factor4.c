/* Created by: Nelson Cardona
 * 
 * This is my attempt at making the MOST EFFICIENT Prime Factor
 * Algorithm. I also did my best to make it portable, using the
 * properties set in float.h such as DBL_MANT_DIG to ensure that
 * the limit for prime factors is set as close as (but not
 * below) sqrt(N) as possible.
 * 
 * ANNOUNCEMENT: I give up. Precision is perfect when casting
 * LITERAL unsigned long long to long double, but lost when
 * casting a variable to unsigned long long. I have no idea why
 * it does this and it is FUCKING. ANNOYING!!!
 */
#include <stdlib.h>
#include <stdio.h>

/* Required for binary properties of floats */
#include <float.h>
/* Required for sqrt() */
#include <tgmath.h>

/* Uncomment this to enable DEBUG mode */
#define DEBUG

/* Defines safe-spot for sqrt() imprecision */
#define BOUND 1U

/* Required for SIZE_MAX */
#ifdef DEBUG
#include <stdint.h>
#endif

static size_t dbl_limit = 0;

size_t compLimit(size_t N) {
	long double a = sqrt((double) N);
#ifdef DEBUG
long double n = N;
printf("computing compLimit() of %.0Lf\n", n);
printf("a = %Lf\n", a);
printf("N - a*a = %Lf\n", ((long double) N) - a*a);
#endif
	if ((long double) N - a*a > BOUND) {
#ifdef DEBUG
printf("It seems that sqrtl(N) = %Lf is TOO DAMN SMALL!!!\n", a);
#endif
		a = ceill((N+a)/(a+1));
	}
#ifdef DEBUG
printf("New limit is now: %zu\n", (size_t) floorl(a));
printf("N - a*a = %Lf\n", ((long double) N) - a*a);
#endif
	return floorl(a);
}

void factor(size_t N) {
	printf("%zu: ", N);
	if (!N) return;
	while (!(N % 2)) {
		printf("2 ");
		N /= 2;
	}

	size_t i = 3;
	//size_t limit = (N < dbl_limit) ? sqrtl(N) : compLimit(N);
	size_t limit = compLimit(N);
	while (i <= limit) {
		while (!(N % i)) {
			printf("%zu ", i);
			N /= i;
			//limit = (N < dbl_limit) ? sqrtl(N) : compLimit(N);
			limit = compLimit(N);
		}
		i += 2;
	}

	if (N > 2)
		printf("%zu ", N);
	
	printf("\n");
}

int main(int argc, char* argv[argc+1]) {
#ifdef DEBUG
printf("Binary representations of floating-point values in current C platform:\n");
printf("\tFLT_RADIX: %d\n", FLT_RADIX);
printf("\tFLT_MANT_DIG: %d\n", FLT_MANT_DIG);
printf("\tDBL_MANT_DIG: %d\n", DBL_MANT_DIG);
printf("\tLDBL_MANT_DIG: %d\n", LDBL_MANT_DIG);
printf("\tLDBL_MAX_EXP: %d\n", LDBL_MAX_EXP);
printf("\nMemory sizes (in bytes) of size_t and all floats:\n");
printf("\tsize_t: %lu\n", sizeof(size_t));
printf("\tfloat: %lu\n", sizeof(float));
printf("\tdouble: %lu\n", sizeof(double));
printf("\tlong double: %lu\n", sizeof(long double));
#endif
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
#ifdef DEBUG
printf("digits have been set to: %d\n", digits);
#endif
#if FLT_RADIX == 2
	dbl_limit = 1ULL << digits;
#else
	dbl_limit = powl(FLT_RADIX, digits);
#endif
#ifdef DEBUG
printf("dbl_limit has now been set to: %zu\n", dbl_limit);
#endif
	for (int i = 1; i < argc; ++i) {
		size_t n = strtoull(argv[i], 0, 0);

		factor(n);
	}

	return EXIT_SUCCESS;
}
