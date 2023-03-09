/* Created by Nelson Cardona
 * Start Time/Date: 17:26/9-03-23
 */
#include <stdlib.h>
#include <stdio.h>

#include <tgmath.h>

/* If either vector dimensions aren't the same dimension as dim,
 * pray you don't get a seg fault XD
 */
double dotProduct(size_t dim, double const vec1[dim], double const vec2[dim]) {
	double result = 0;

	for(size_t i = 0; i < dim; ++i)
		result += vec1[i] * vec2[i];

	return result;
}

void linearTransform(size_t domain, size_t range, double const matrix[range][domain], double const vec[domain], double result[range]) {
	for (size_t i = 0; i < range; ++i) {
		result[i] = dotProduct(domain, matrix[i], vec);
	}
}

void printVector(size_t dim, double const vec[dim]) {
		printf("{");
		for (size_t i = 0; i < dim; ++i) {
			printf("%.3f", vec[i]);
			if (i < dim - 1)
				printf(", ");
		}
		printf("}\n");
}
int main(int argc, char* argv[argc+1]) {
	if (argc < 2) {
		printf("Program expects at least one input. Exiting...\n");
		return EXIT_FAILURE;
	}
	double const Rx[3][3] = {
		[0] = {[0] = 1,},
		[1] = {[1] = 1/sqrt(2), [2] = -1/sqrt(2),},
		[2] = {[1] = 1/sqrt(2), [2] = 1/sqrt(2),},
	};
	double const Ry[3][3] = {
		[0] = {[0] = 1/sqrt(2), [2] = 1/sqrt(2),},
		[1] = {[1] = 1,},
		[2] = {[0] = -1/sqrt(2), [2] = 1/sqrt(2),},
	};
	double const Rz[3][3] = {
		[0] = {[0] = 1/sqrt(2), [1] = -1/sqrt(2),},
		[1] = {[0] = 1/sqrt(2), [1] = 1/sqrt(2),},
		[2] = {[2] = 1,},
	};
	
	double vec[argc - 1];
	for (size_t i = 1; i < argc; ++i)
		vec[i - 1] = strtod(argv[i], 0);

	printf("The modulus is: sqrt(%.3f)\n", dotProduct(argc - 1, vec, vec));

	if (argc - 1 == 3) {
		double result[argc - 1];
		for (size_t i = 0; i < argc - 1; ++i)
			result[i] = 0;

		printf("Rotating vector 45 degrees along x-axis.\n");
		linearTransform(argc - 1, argc - 1, Rx, vec, result);
		printf("Rotated vector is:\n");
		printVector(argc - 1, result);

		printf("Rotating vector 45 degrees along y-axis.\n");
		linearTransform(argc - 1, argc - 1, Ry, vec, result);
		printf("Rotated vector is:\n");
		printVector(argc - 1, result);

		printf("Rotating vector 45 degrees along z-axis.\n");
		linearTransform(argc - 1, argc - 1, Rz, vec, result);
		printf("Rotated vector is:\n");
		printVector(argc - 1, result);
	}

	return EXIT_SUCCESS;
}

