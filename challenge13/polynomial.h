/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:03
 */
/** @file polynomial.h */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>
#include <stdbool.h>
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
  * Checks whether polynomial is essentially zero.
  * @param p_ptr Pointer to polynomial struct.
  * @return whether every coefficient in p_ptr is zero.
  */
bool poly_is_zero(polynomial const* p_ptr);

/**
  * Divides polynomial `dividend` by polynomial `divisor` and
  * stores result in `dividend`.
  * @param dividend Pointer to dividend where quotient will
  *			be stored.
  * @param divisor Pointer to polynomial that divides
  *			dividend.
  * @result true if remainder is zero (using poly_is_zero()).
  * @note Quotient is returned in this way because we are not
  *			up to `malloc()`, yet.
  * @note `nr` in `divnr` means "no remainder".
  */
bool poly_divnr(polynomial* dividend, polynomial const* divisor);
void poly_print(polynomial const* poly_ptr);
#endif
