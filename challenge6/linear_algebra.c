/* Created by Nelson Cardona
 * Start Time/Date: 17:26/9-03-23
 * Completion Time/Date: 14:02/10-03-23* (Haven't done at interative version
 * of the matrix inverse, but I spent too long on this so cbf.
 * The calculation of the determinant is so computationally inefficient
 * that it will end up being the bottleneck in the matrix inverse calculation
 * for large dimensions XD
 * I didn't even need to add it as a precondition because the method used
 * to calc the inverse is Gauss Elimination, so no errors would have been thrown.
 * Really, the determinant was for fun. I seem to be addicted to pain D:
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

/* If either vectors' dimensions aren't the same dimension as dim,
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
printf("\n");
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
#ifdef DEBUG
printf("New row is:\n");
printVector(dim, matrix[row_dest]);
printf("\n");
#endif
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
	printf("The row echelon form of matrix is:\n");
	printMatrix(rows, cols, result);
}

void rref(size_t rows, size_t cols, double const matrix[rows][cols]) {
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
	printf("The REDUCED row echelon form of matrix is:\n");
	printMatrix(rows, cols, result);
}

/* CHEATING AT THIS POINT, I KNOW!!! */
double det(size_t dim, double const matrix[dim][dim]);

double minor(size_t dim, double const matrix[dim][dim], size_t row, size_t col) {
	double del_matrx[dim-1][dim-1];

	size_t del_row = 0;
	size_t del_col = 0;
	for (size_t i = 0; i < dim; ++i) {
		if (i == row) continue;
		del_col = 0;
		for (size_t j = 0; j < dim; ++j) {
			if (j == col) continue;
			del_matrx[del_row][del_col] = matrix[i][j];
			++del_col;
		}
		++del_row;
	}
#ifdef DEBUG
printf("Deleting row %zu and col %zu gives:\n", row, col);
printMatrix(dim-1, dim-1, del_matrx);
printf("\n");
#endif

	return det(dim-1, del_matrx);
}

double det(size_t dim, double const matrix[dim][dim]) {
	if (dim == 1) return matrix[0][0];
	double result = 0;
	for (size_t i = 0; i < dim; ++i) {
		result += matrix[0][i] * pow(-1, i) * minor(dim, matrix, 0, i);
#ifdef DEBUG
printf("result is currently: %.3f\n", result);
#endif
	}

	return result;
}

void calcInverse(size_t dim, double dest[dim][dim], double const src[dim][dim]) {
	if (fabs(det(dim, src)) < eps) {
		printf("Determinant of matrix is 0. Can't compute inverse.\n");
		return;
	}
	double result[dim][dim];
	copyMatrix(dim, dim, result, src);

	for (size_t i = 0; i < dim; ++i) {
		for (size_t j = 0; j < dim; ++j) {
			/* I could do dest[i][j] = (i == j); but I'm  avoiding implicit
			 * conversions for this course
			 */
			dest[i][j] = (i == j) ? 1 : 0;
		}
	}

#ifdef DEBUG
printf("Matrix before RREF:\n");
printMatrix(dim, dim, dest);
printf("\n");
#endif

	size_t rank = 0;
	for (size_t i = 0; i < dim; ++i) {
#ifdef DEBUG
printf("Checking column %zu\n", i);
#endif
		size_t j = rank;
		while (fabs(result[j][i]) < eps && j < dim)
			++j;
		if (j == dim) {
#ifdef DEBUG
printf("Bad column\n");
#endif
			continue;
		}
#ifdef DEBUG
printf("Stopped @ row %zu\n", j);
#endif
		swapRow(dim, result, rank, j);
		swapRow(dim, dest, rank, j);
		double rank_head = result[rank][i];
		rowMult(dim, result, 1/rank_head, rank);
		rowMult(dim, dest, 1/rank_head, rank);
		for (size_t k = 0; k < dim; ++k) {
#ifdef DEBUG
printf("Working on row %zu\n", k);
#endif
			if (k == rank)
				continue;
			double k_head = result[k][i];
			rowAdd(dim, result, -k_head, k, rank);
			rowAdd(dim, dest, -k_head, k, rank);
		}
		++rank;
#ifdef DEBUG
printf("Rank is now %zu\n", rank);
#endif
	}
	printMatrix(dim, dim, dest);
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
		printf("\n");
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

	printf("Computing row echelon form of Matrix:\n");
	printMatrix(4, 5, testMatrix);
	printf("\n");
	rowEchelon(4, 5, testMatrix);
	printf("\n");
	printf("Computing row echelon form of Matrix:\n");
	printMatrix(4, 5, testMatrix);
	printf("\n");
	rowEchelon(6, 3, testMatrix2);
	printf("\n");

	printf("Computing REDUCED row echelon form of Matrix:\n");
	printMatrix(4, 5, testMatrix);
	printf("\n");
	rref(4, 5, testMatrix);
	printf("\n");
	printf("Computing REDUCED row echelon form of Matrix:\n");
	printMatrix(4, 5, testMatrix);
	printf("\n");
	rref(6, 3, testMatrix2);
	printf("\n");

	double inverse[3][3];

	printf("The inverse of Rx is:\n");
	calcInverse(3, inverse, Rx);
	printf("\n");
	printf("The inverse of Ry is:\n");
	calcInverse(3, inverse, Ry);
	printf("\n");
	printf("The inverse of Rz is:\n");
	calcInverse(3, inverse, Rz);
	printf("\n");

	double const square[5][5] = {
		[0] = {1, 2, 3, 4, 5},
		[1] = {5, 4, 3, 2, 1},
		[2] = {0, 1, 2, 3, 4},
		[3] = {4, 3, 2, 1, 0},
		[4] = {2, 4, 6, 8, 0},
	};

	printf("Determinant of square is: %.3f\n", det(5, square));
	printf("The inverse of square is:\n");
	double inv5[5][5] = {0};
	calcInverse(5, inv5, square);
	printf("\n");

	double const square2[2][2] = {
		[0] = {1, 2},
		[1] = {27, 42},
	};

	printf("Determinant of square2 is: %.3f\n", det(2, square2));
	printf("The inverse of square2 is:\n");
	double inv2[2][2] = {0};
	calcInverse(2, inv2, square2);
	printf("\n");

	double const square3[6][6] = {
		[0] = {20, 5, 0, 0, 0, 0},
		[1] = {-5, 1, -M_PI, 0, 0, 0},
		[2] = {0, 100, 0, 4, 69, 1},
		[3] = {M_PI_4, 0, 0, 0, 16, -3.25},
		[4] = {0, 0, 1, 0, 0, 5.42},
		[5] = {0, 36.1, -4, 15, 22, 10},
	};

	printf("Determinant of square3 is: %.3f\n", det(6, square3));
	printf("The inverse of square3 is:\n");
	double inv6[6][6] = {0};
	calcInverse(6, inv6, square3);
	printf("\n");

	return EXIT_SUCCESS;
}

