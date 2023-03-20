/* Created by: Nelson Cardona
 * Start Time/Date: 14:50/20-03-2023
 * Completion Time/Date: 15:29/20-03-2023
 * 
 * I was honestly quite surprised that the algorithm works for unbelievable
 * large values such as SIZE_MAX since I was using sqrt(), which converts
 * the input into a double.
 * I did some more testing and it I realised that SIZE_MAX STILL loses
 * precision when converted to double, but the square root is still close
 * enough to the real square root that the algorithm can still compute the
 * prime factors. However, I got lucky in this case since the largest prime
 * factors were nowhere near the sqrt() to be affected. But I can't say the
 * same for other very large numbers. Therefore, I must declare the behaviour
 * of this algoritm as UB when using sqrt().
 *
 * Unfortunately, if I used something like n/2 instead of sqrt(n), then the
 * runtime of the algorithm becomes painfully long for very large values.
 * Or, for certain value, because I tested SIZE_MAX and SIZE_MAX-1 and I
 * got answers INSTANTLY, whereas an arbitray value like SIZE_MAX-29384
 * took too damn long. Also, n/2 isn't larger than sqrt(n) for smaller vals.
 * I honestly have no idea, anymore :(
 */
#include <stdlib.h>
#include <stdio.h>

#include <tgmath.h>

/* Computes the smallest prime factor of n */
size_t minPrimeFactor(size_t n) {
	for (size_t i = 2; i <= n/2; ++i) {
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
