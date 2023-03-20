/* Created by: Nelson Cardona
 * Start Time/Date: 14:50/20-03-2023
 * Completion Time/Date: 
 */
#include <stdlib.h>
#include <stdio.h>

/* Computes the smallest prime factor of n */
size_t minPrimeFactor(size_t n) {
	return 0;
}

/* Computes the prime factors of N */
void factor(size_t N) {
	// STUB...
}

int main(int argc, char* argv[argc+1]) {
	for (int i = 1; i < argc; ++i) {
		size_t const N = strtoull(argv[i], 0, 0);

		factor(N);
	}

	return EXIT_SUCCESS;
}
