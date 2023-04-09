/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/20:06
 */
#include "polynomial.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <tgmath.h>

/**
  * `struct` representing a polynomial.
  * @note	The number of coefficients a polynomial has is one more than its degree.
  */
struct polynomial {
	size_t degree;	///< The degree of the polynomial.
	double* coeff;	///< The coefficients of the polynomial.
};

polynomial* poly_init(polynomial* p, size_t degree, double const coeff[degree+1]) {
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

polynomial* poly_new(size_t degree, double const coeff[degree+1]) {
	return poly_init(malloc(sizeof(polynomial)), degree, coeff);
}

void poly_delete(polynomial* p) {
	free(p->coeff);
	free(p);
}

polynomial* poly_resize(polynomial* p, size_t new_degree) {
	if (p && p->degree != new_degree) {
		double* new_coeff = realloc(p->coeff, sizeof(double[new_degree+1]));
		if (!new_coeff)
			return 0;
		if (poly_getdegree(p) < new_degree) {
			for (size_t i = p->degree+1; i <= new_degree; ++i)
				new_coeff[i] = 0;
		}
		p->degree = new_degree;
		p->coeff = new_coeff;
	}
	return p;
}

size_t poly_getdegree(polynomial const* p) {
assert(p);
	return p->degree;
}

double poly_getcoeff(polynomial const* p, size_t n) {
assert(p);
	return (n <= poly_getdegree(p)) ? p->coeff[n] : 0.0;
}

polynomial* poly_add(polynomial* dest, polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = poly_getdegree(dest);
		size_t src_degree = poly_getdegree(src);
		size_t max_degree = (dest_degree > src_degree) ? dest_degree : src_degree;

		if (dest_degree < max_degree) {
			if (!poly_resize(dest, max_degree))
				return 0;
		}
		if (!vector_add(max_degree+1, dest->coeff, src->coeff))
			return 0;
		return dest;
	}
	return 0;
}

polynomial* poly_mult(polynomial* dest, double k) {
	if (dest) {
		if (!vector_mult(poly_getdegree(dest)+1, dest->coeff, k))
			return 0;
	}
	return dest;
}

polynomial* poly_div(polynomial* dest, polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = poly_getdegree(dest);
		size_t src_degree = poly_getdegree(src);
		if (dest_degree < src_degree)
			return 0;
		size_t quot_degree = dest_degree - src_degree;
		double* quot_coeff = malloc((quot_degree+1)*sizeof(double));
		if (!quot_coeff)
			return 0;

		for (size_t i = 0; i <= quot_degree; ++i) {
			quot_coeff[quot_degree-i] = dest->coeff[dest_degree-i]/src->coeff[src_degree];
			for (size_t j = 0; j <= src_degree; ++j) {
				dest->coeff[dest_degree-i-j] -= quot_coeff[quot_degree-i]
					* src->coeff[src_degree-j];
			}
		}

		free(dest->coeff);
		dest->degree = quot_degree;
		dest->coeff = quot_coeff;
		
		return dest;
	}
	return 0;
}

double polynomial_compute(polynomial const* p, double x) {
	double ret = 0.0;
	if (p) {
		for (size_t i = 0; i <= poly_getdegree(p); ++i)
			ret += i ? poly_getcoeff(p, i)*pow(x, i) : poly_getcoeff(p, i);
	}
	return ret;
}

void poly_print(polynomial const* p) {
	if (p)
		vector_print(poly_getdegree(p)+1, p->coeff);
	else
		vector_print(0, 0);
}
