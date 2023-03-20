/* Created by: Nelson Cardona
 * Start Time/Date: 14:50/20-03-2023
 * Completion Time/Date: 15:29/20-03-2023
 * 
 * I was honestly quite surprised that the algorithm works for unbelievably
 * large values such as SIZE_MAX since I was using sqrt(), which converts
 * the input into a double.
 *
 * I did some more testing and it I realised that SIZE_MAX STILL loses
 * precision when converted to double, but the smallest prime factors
 * tended to be too small to be anywhere near sqrt(n). This is only a
 * problem if there was somehow a prime factor VERY CLOSE to sqrt(n) and
 * the imprecision forces the algorithm to miss it and return n, instead,
 * thinking n is prime. I don't know if it's possible for a prime factor
 * to be close enough to sqrt(n) for floating point imprecision to create
 * an error, but I will err on the side of caution and conclude that
 * floating point imprecision leads to UB in this algorithm (for very large
 * values).
 *
 * Unfortunately, if I used something like n/2 instead of sqrt(n), then the
 * runtime of the algorithm becomes painfully long for very large values.
 * Or, for certain value, because I tested SIZE_MAX and SIZE_MAX-1 and I
 * got answers INSTANTLY, whereas an arbitray value like SIZE_MAX-29384
 * took too damn long. Also, n/2 isn't larger than sqrt(n) for smaller vals.
 *
 * I honestly have no idea, anymore :(
 */
#include <stdlib.h>
#include <stdio.h>

#include <tgmath.h>

/* Computes the smallest prime factor of n */
size_t minPrimeFactor(size_t n) {
	for (size_t i = 2; i <= sqrt(n); ++i) {
		if (!(n % i))
			return i;
	}

	return n; // n is PRIME at this point
}

/* Computes the prime factors of N */
void factor(size_t N) {
	printf("The prime factors of %zu are:\n", N);
	while (N > 1) {
		size_t minPrime = minPrimeFactor(N);
		printf("%zu ", minPrime);
		N /= minPrime;
	}
	printf("\n");
}

int main(int argc, char* argv[argc+1]) {
	for (int i = 1; i < argc; ++i) {
		size_t const N = strtoull(argv[i], 0, 0);

		factor(N);
	}

	return EXIT_SUCCESS;
}
