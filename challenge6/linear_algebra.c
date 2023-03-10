/* Created by Nelson Cardona
 * Start Time/Date: 17:26/9-03-23
 */
#include <stdlib.h>
#include <stdio.h>

#include <tgmath.h>

/* Uncomment to enable DEBUG mode */
//#define DEBUG

double const eps = 0x1P-16;

void printVector(size_t dim, double const vec[dim]) {
	printf("{");
	for (size_t i = 0; i < dim; ++i) {
		printf("%.3f", vec[i]);
		if (i < dim - 1)
			printf(", ");
	}
	printf("}\n");
}

void printMatrix(size_t rows, size_t cols, double const matrix[rows][cols]) {
	for (size_t i = 0; i < rows; ++i) {
		printf("{\t");
		for (size_t j = 0; j < cols; ++j) {
			printf("%.3f", matrix[i][j]);
			if (j < cols - 1)
				printf(",");
			printf("\t");
		}
		printf("}\n");
	}
}

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

void copyVector(size_t dim, double dest[dim], double const src[dim]) {
	for (size_t i = 0; i < dim; ++i)
		dest[i] = src[i];
}

void copyMatrix(size_t rows, size_t cols, double dest[rows][cols], double const src[rows][cols]) {
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j)
			dest[i][j] = src[i][j];
	}
}

void scalarMult(size_t dim, double vec[dim], double scalar) {
#ifdef DEBUG
printf("Multiplying %.3f with vector:\n", scalar);
printVector(dim, vec);
#endif
	for (size_t i = 0; i < dim; ++i)
		vec[i] *= scalar;
#ifdef DEBUG
printf("Gives:\n");
printVector(dim, vec);
printf("\n");
#endif
}

void vectorAdd(size_t dim, double dest[dim], double const src[dim]) {
#ifdef DEBUG
printf("Adding vectors:\n");
printVector(dim, dest);
printVector(dim, src);
#endif
	for (size_t i = 0; i < dim; ++i)
		dest[i] += src[i];
#ifdef DEBUG
printf("Gives:\n");
printVector(dim, dest);
printf("\n");
#endif
}

void swapRow(size_t dim, double matrix[][dim], size_t r1, size_t r2) {
#ifdef DEBUG
printf("Swapping row %zu w/ row %zu\n", r1, r2);
#endif
	double buf[dim];

	copyVector(dim, buf, matrix[r1]);
	copyVector(dim, matrix[r1], matrix[r2]);
	copyVector(dim, matrix[r2], buf);
}

void rowMult(size_t dim, double matrix[][dim], double scalar, size_t row_dest) {
#ifdef DEBUG
printf("Multiplying %.3f into row %zu:\n", scalar, row_dest);
printVector(dim, matrix[row_dest]);
printf("\n");
#endif
	for (size_t i = 0; i < dim; ++i)
		matrix[row_dest][i] *= scalar;
#ifdef DEBUG
printf("Row %zu is now:\n", row_dest);
printVector(dim, matrix[row_dest]);
printf("\n");
#endif
}

void rowAdd(size_t dim, double matrix[][dim], double scalar, size_t row_dest, size_t row_src) {
#ifdef DEBUG
printf("Adding row %zu to row %zu using scalar multiple %.3f\n", row_src, row_dest, scalar);
#endif
	for (size_t i = 0; i < dim; ++i)
		matrix[row_dest][i] += scalar*matrix[row_src][i];
}

void rowEchelon(size_t rows, size_t cols, double const matrix[rows][cols]) {
	double result[rows][cols];
	copyMatrix(rows, cols, result, matrix);

	size_t rank = 0;
	for (size_t i = 0; i < cols; ++i) {
#ifdef DEBUG
printf("Checking column %zu\n", i);
#endif
		size_t j = rank;
		while (fabs(result[j][i]) < eps && j < rows)
			++j;
		if (j == rows) {
#ifdef DEBUG
printf("Bad column\n");
#endif
			continue;
		}
#ifdef DEBUG
printf("Stopped @ row %zu\n", j);
#endif
		//scalarMult(cols, result[j], 1/result[j][i]);
		swapRow(cols, result, rank, j);
		for (size_t k = rank + 1; k < rows; ++k) {
#ifdef DEBUG
printf("Working on row %zu\n", k);
#endif
			rowAdd(cols, result, -result[k][i]/result[rank][i], k, rank);
		}
		++rank;
#ifdef DEBUG
printf("Rank is now %zu\n", rank);
#endif
	}
	printMatrix(rows, cols, result);
}

void gaussElim(size_t rows, size_t cols, double const matrix[rows][cols]) {
	double result[rows][cols];
	copyMatrix(rows, cols, result, matrix);

	size_t rank = 0;
	for (size_t i = 0; i < cols; ++i) {
#ifdef DEBUG
printf("Checking column %zu\n", i);
#endif
		size_t j = rank;
		while (fabs(result[j][i]) < eps && j < rows)
			++j;
		if (j == rows) {
#ifdef DEBUG
printf("Bad column\n");
#endif
			continue;
		}
#ifdef DEBUG
printf("Stopped @ row %zu\n", j);
#endif
		swapRow(cols, result, rank, j);
		rowMult(cols, result, 1/result[rank][i], rank);
		for (size_t k = 0; k < rows; ++k) {
#ifdef DEBUG
printf("Working on row %zu\n", k);
#endif
			if (k == rank)
				continue;
			rowAdd(cols, result, -result[k][i], k, rank);
		}
		++rank;
#ifdef DEBUG
printf("Rank is now %zu\n", rank);
#endif
	}
	printMatrix(rows, cols, result);
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

	double copy[argc - 1];
	copyVector(argc - 1, copy, vec);
	double scalar = 15;

	printf("Multiplying vector by %.3f gives:\n", scalar);
	scalarMult(argc - 1, copy, scalar);
	printVector(argc - 1, copy);

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

	double const testMatrix[4][5] = {
		[0] = {0, 0, 3, 2, 3},
		[1] = {0, 4, 5, 2.5, -3},
		[2] = {0, 3, 7, -24, 1},
		[3] = {0, 20, 3, 5, 7},
	};
	double const testMatrix2[6][3] = {
		[0] = {0, 0, 2,},
		[1] = {0, -M_PI_4, 5,},
		[2] = {2, 3, 7,},
		[3] = {0, 20, 3,},
		[4] = {1, 1, 1,},
		[5] = {1, 0, 3},
	};

	printf("The row echelon form of matrix 1 is:\n");
	rowEchelon(4, 5, testMatrix);
	printf("\n");
	printf("The row echelon form of matrix 2 is:\n");
	rowEchelon(6, 3, testMatrix2);
	printf("\n");

	printf("The REDUCED row echelon form of matrix 1 is:\n");
	gaussElim(4, 5, testMatrix);
	printf("\n");
	printf("The REDUCED row echelon form of matrix 2 is:\n");
	gaussElim(6, 3, testMatrix2);
	printf("\n");

	return EXIT_SUCCESS;
}

