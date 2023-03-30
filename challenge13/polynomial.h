/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:03
 */
/** @file polynomial.h */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>
#include <complex.h>

typedef struct polynomial polynomial;

struct polynomial {
	size_t degree;
	double* coeff;
};

#ifndef __STDC_NO_COMPLEX__
typedef struct cmplx_polynomial cmplx_polynomial;

struct cmplx_polynomial {
	size_t degree;
	double complex* coeff;
};
#endif

polynomial* poly_get(polynomial* poly_pty, size_t degree, double coeff[degree+1]);

/**
  * Divides polynomial `dividend` by polynomial `divisor` and
  * stores result in `dividend`.
  * @param dividend Pointer to dividend where quotient will
  *			be stored.
  * @param divisor Pointer to polynomial that divides
  *			dividend.
  * @note Result is returned in this way because we are
  *			up to `malloc()`, yet.
  * @note `nr` in `divnr` means "no remainder".
  */
void poly_divnr(polynomial* p_ptr1, polynomial* p_ptr2);
void poly_print(polynomial* poly_ptr);
#endif
