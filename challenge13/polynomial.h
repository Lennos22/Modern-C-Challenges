/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:03
 */
/** @file polynomial.h */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "numerical_derivative.h"

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
  * @note Quotient is returned in this way because we are not
  *			up to `malloc()`, yet.
  * @note `nr` in `divnr` means "no remainder".
  */
void poly_divnr(polynomial* dividend, polynomial const* divisor);

/**
  * Computes all the REAL roots of a polynomial
  *
  * This was implemented very badly since I wanted to recycle my
  * newton_raphson() prototype. Don't worry, when I learn malloc(),
  * I'll come back to this problem and do it properly
  *
  * @param poly_func Pointer to the polynomial function.
  * @param x_initial The initial guess for a root.
  * @note This function uses the [Newton-Raphson] method to compute
  *			the roots.
  * @param p_ptr Pointer to the polynomial struct.
  * @note Currently, this is embedded into poly_func using a global
  *			variable in main(). Again, I know it's bad.
  * @param roots An array of doubles to output the root.
  * @return the total number of REAL roots (counting multiplicity).
  */
size_t poly_real_roots(diff_function* poly_func, double x_initial, polynomial * p_ptr, double roots[p_ptr->degree]);

/**
  * Prints a polynomial represented by a polynomial struct onto stdin.
  * @param poly_pty The polynomial struct to print.
  */
void poly_print(polynomial const* poly_ptr);
#endif
