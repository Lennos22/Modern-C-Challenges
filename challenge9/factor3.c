/* Created by: Nelson Cardona
 * 
 * A more sensible algorithm that does away with the use of
 * minPrimeFactor(). Found this in GeeksforGeeks
 */
#include <stdlib.h>
#include <stdio.h>

void factor(size_t N) {
	printf("The prime factors of %zu are:\n", N);
	if (!N)
		return;
	while (!(N % 2)) {
		printf("2 ");
		N /= 2;
	}

	/* N/2 should work since N/2 > sqrt(N) for N >= 4! */
	for (size_t i = 3; i < N/2; i += 2) {
		while (!(N % i)) {
			printf("%zu ", i);
			N /= i;
		}
	}

	if (N > 2)
		printf("%zu ", N);
	
	printf("\n");
}

int main(int argc, char* argv[argc+1]) {
	for (int i = 1; i < argc; ++i) {
		size_t n = strtoull(argv[i], 0, 0);

		factor(n);
	}

	return EXIT_SUCCESS;
}
