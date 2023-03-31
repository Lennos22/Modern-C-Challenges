/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/12:54
 */
#include "polynomial.h"
#include "newton_raphson.h"

#define NDEBUG

#include <stdio.h>
#include <tgmath.h>

#ifndef NAN
#error "NAN value is not supported. Cannot run poly_real_roots() or poly_cmplx_roots()..."
#endif

static int const dec_places = 7;

polynomial* poly_get(polynomial* poly_ptr, size_t degree, double coeff[degree+1]) {
	// FUNCTION STUB. Fill in after learning malloc()...
	return (void*)0;
}

void poly_divnr(polynomial* dividend, polynomial const* divisor) {
	if (dividend->degree < divisor->degree) {
		fprintf(stderr, "Divisor is of larger degree than dividend...\n");
		return;
	}
	size_t quot_degree = dividend->degree - divisor->degree;
	double quot_coeff[quot_degree+1];
#ifndef NDEBUG
polynomial quotient = {
	.degree = quot_degree,
	.coeff = quot_coeff,
};
#endif

	for (size_t i = dividend->degree; i >= divisor->degree; --i) {
		quot_coeff[i-divisor->degree] = dividend->coeff[i]/divisor->coeff[divisor->degree];
#ifndef NDEBUG
printf("quot_coeff[%zu] = %g\n", i-divisor->degree, quot_coeff[i-divisor->degree]);
#endif
		for (size_t j = i; j >= i-divisor->degree; --j) {
			dividend->coeff[j] -= quot_coeff[i-divisor->degree]*divisor->coeff[divisor->degree-(i-j)];
			if (!j) break;
		}
#ifndef NDEBUG
printf("dividend is now:\n");
poly_print(dividend);
#endif
		if (!i) break;
	}
#ifndef NDEBUG
printf("Final quotient is:\n");
poly_print(&quotient);
#endif

	/* Copy quotient into dividend */
	dividend->degree = quot_degree;
	for (size_t i = 0; i <= quot_degree; ++i)
		dividend->coeff[i] = quot_coeff[i];
}

size_t poly_real_roots(diff_function* poly_func, double x_initial, polynomial* p_ptr, double roots[p_ptr->degree]) {
	size_t degree = p_ptr->degree;
	size_t num_roots = 0;

	for (num_roots = 0; num_roots < degree; ++num_roots) {
		roots[num_roots] = newton_raphson(poly_func, x_initial, dec_places);
#ifndef NDEBUG
printf("roots[%zu] = %g\n", num_roots, roots[num_roots]);
#endif
		if (!isfinite(roots[num_roots])) {
			if (!num_roots)
				printf("Could not find any roots in polynomial. Your initial guess may have hit "	\
						"a stationary point.\n");
			break;
		}
		polynomial factor = {
			.degree = 1,
			.coeff = (double[2]) { 
				[1] = 1,
				[0] = -roots[num_roots],
			},
		};

		poly_divnr(p_ptr, &factor);
#ifndef NDEBUG
printf("Polynomial is now reduced to:\n");
poly_print(p_ptr);
#endif
	}

	return num_roots;
}

void poly_print(polynomial const* poly_ptr) {
	for (size_t i = 0; i <= poly_ptr->degree; ++i) {
		printf("%g", fabs(poly_ptr->coeff[poly_ptr->degree-i]));
		if (i != poly_ptr->degree) {
			if (poly_ptr->coeff[poly_ptr->degree-(i+1)] < 0)
				printf("x^%zu - ", poly_ptr->degree-i);
			else
				printf("x^%zu + ", poly_ptr->degree-i);
		}
	}
	printf("\n");
}

#ifndef __STDC_NO_COMPLEX__
void cmplx_poly_divnr(cmplx_polynomial* dividend, cmplx_polynomial const* divisor) {
	if (dividend->degree < divisor->degree) {
		fprintf(stderr, "Divisor is of larger degree than dividend...\n");
		return;
	}
	size_t quot_degree = dividend->degree - divisor->degree;
	double complex quot_coeff[quot_degree+1];
#ifndef NDEBUG
cmplx_polynomial quotient = {
	.degree = quot_degree,
	.coeff = quot_coeff,
};
#endif

	for (size_t i = dividend->degree; i >= divisor->degree; --i) {
		quot_coeff[i-divisor->degree] = dividend->coeff[i]/divisor->coeff[divisor->degree];
#ifndef NDEBUG
printf("quot_coeff[%zu] = %g+i*%g\n", i-divisor->degree, creal(quot_coeff[i-divisor->degree]), cimag(quot_coeff[i-divisor->degree]));
#endif
		for (size_t j = i; j >= i-divisor->degree; --j) {
			dividend->coeff[j] -= quot_coeff[i-divisor->degree]*divisor->coeff[divisor->degree-(i-j)];
			if (!j) break;
		}
#ifndef NDEBUG
printf("dividend is now:\n");
cmplx_poly_print(dividend);
#endif
		if (!i) break;
	}
#ifndef NDEBUG
printf("Final quotient is:\n");
cmplx_poly_print(&quotient);
#endif

	/* Copy quotient into dividend */
	dividend->degree = quot_degree;
	for (size_t i = 0; i <= quot_degree; ++i)
		dividend->coeff[i] = quot_coeff[i];
}

size_t poly_cmplx_roots(cmplx_diff_function* cmplx_poly_func, double complex z_initial, cmplx_polynomial* cp_ptr, double complex roots[cp_ptr->degree]) {
	size_t degree = cp_ptr->degree;
	size_t num_roots = 0;

	for (num_roots = 0; num_roots < degree; ++num_roots) {
		roots[num_roots] = cmplx_newton_raphson(cmplx_poly_func, z_initial, dec_places);
#ifndef NDEBUG
printf("roots[%zu] = %g+i*%g\n", num_roots, creal(roots[num_roots]), cimag(roots[num_roots]));
#endif
		/* This check is no longer required courtesy of the Fundamental Theorem
		 * of Algebra!!!
		 *
		 * JUST KIDDING!!! It's still needed on the off (off, off, off, ...) chance your initial
		 * guess hits PRECISELY at a stationary point.
		 */
		if (!isfinite(creal(roots[num_roots])) || !isfinite(creal(roots[num_roots]))) {
			fprintf(stderr, "Unable to find root using Newton-Raphson. Your initial guess may have"	\
					" been a stationary point...\n");
			break;
		}
		cmplx_polynomial factor = {
			.degree = 1,
			.coeff = (double complex[2]) { 
				[1] = 1,
				[0] = -roots[num_roots],
			},
		};

		cmplx_poly_divnr(cp_ptr, &factor);
#ifndef NDEBUG
printf("Polynomial is now reduced to:\n");
cmplx_poly_print(cp_ptr);
#endif
	}

	return num_roots;
}

void cmplx_poly_print(cmplx_polynomial const* cmplx_poly_ptr) {
	for (size_t i = 0; i <= cmplx_poly_ptr->degree; ++i) {
		printf("(%g+i*%g)", creal(cmplx_poly_ptr->coeff[cmplx_poly_ptr->degree-i]), cimag(cmplx_poly_ptr->coeff[cmplx_poly_ptr->degree-i]));
		if (i != cmplx_poly_ptr->degree) {
			printf("z^%zu + ", cmplx_poly_ptr->degree-i);
		}
	}
	printf("\n");
}
#endif
