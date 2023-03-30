/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/12:54
 */
#include "polynomial.h"

#include <stdio.h>

polynomial* poly_get(polynomial* poly_ptr, size_t degree, double coeff[degree+1]) {
	// FUNCTION STUB. Fill in after learning malloc()...
	return (void*)0;
}

void poly_divnr(polynomial* dividend, polynomial* divisor) {
	if (dividend->degree < divisor->degree) {
		fprintf(stderr, "Divisor is of larger degree than dividend...\n");
		return;
	}
	size_t quot_degree = dividend->degree - divisor->degree;
	double quot_coeff[quot_degree];
	polynomial quotient = {
		.degree = quot_degree,
		.coeff = quot_coeff,
	};
	double rem_coeff[quot_degree];
	polynomial remainder = {
		.degree = quot_degree,
		.coeff = rem_coeff,
	};


}

void poly_print(polynomial* poly_ptr) {
	for (size_t i = 0; i <= poly_ptr->degree; ++i) {
		printf("%gx^%zu", poly_ptr->coeff[poly_ptr->degree-i], poly_ptr->degree-i);
		if (i == poly_ptr->degree)
			printf("\n");
		else
			printf(" + ");
	}
}
