/* Created by: Nelson Cardona
 * OHHHHH, I know why it takes long for some very large values. It depends
 * on how far apart the prime factors are from each other or how large the
 * prime factors get. Larger prime factors take longer to find!
 *
 * This is a modified algorithm that process all the even prime factors
 * (i.e. 2) before the rest, which will be odd. Should halve the
 * processing time, but it could still get messy for very large prime
 * factors - or even worse, LARGE PRIMES.
 */
#include <stdlib.h>
#include <stdio.h>

#include <tgmath.h>

/* Computes the smallest prime factor of n */
size_t minPrimeFactor(size_t n) {
	for (size_t i = 3; i <= sqrt(n); i += 2) {
		if (!(n % i))
			return i;
	}

	return n; // n is PRIME at this point
}

/* Computes the prime factors of N */
void factor(size_t N) {
	printf("The prime factors of %zu are:\n", N);
	while (!(N % 2) && N) {
		printf("2 ");
		N /= 2;
	}

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
