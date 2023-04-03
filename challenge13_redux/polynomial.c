/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/20:06
 */
#include "polynomial.h"

#include <stdlib.h>
#include <stdio.h>

struct polynomial {
	size_t degree;
	double* coeff;
};

polynomial* poly_init(polynomial* p, size_t degree, double coeff[degree+1]) {
	if (p) {
		*p = (polynomial) {
			.degree = degree,
				.coeff = malloc(sizeof(double[degree+1])),
		};
		if (coeff) {
			for (size_t i = 0; i <= degree; ++i)
				p->coeff[i] = coeff[i];
		} else {
			for (size_t i = 0; i <= degree; ++i)
				p->coeff[i] = 0;
		}
		if (!p->coeff)
			p = 0;
	}
	return p;
}

polynomial* poly_new(size_t degree, double coeff[degree+1]) {
	return poly_init(malloc(sizeof(polynomial)), degree, coeff);
}

void poly_delete(polynomial* p) {
	free(p->coeff);
	free(p);
}

size_t poly_getdegree(polynomial* p) {
	return p->degree;
}

void poly_print(polynomial* p) {
	putc('[', stdout);
	if (p) {
		for (size_t i = 0; i <= poly_getdegree(p); ++i) {
			printf("%g", p->coeff[i]);
			if (i < poly_getdegree(p))
				printf(", ");
		}
	}
	putc(']', stdout);
}
