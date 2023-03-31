/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:03
 */
/** @file polynomial.h */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "numerical_derivative.h"
#include "complx_num_derivative.h"

#include <stddef.h>
#include <complex.h>

typedef struct polynomial polynomial;

/**
  * Polynomial struct using an array to encapsulate the coefficients.
  */
struct polynomial {
	size_t degree;			///< The degree of the polynomial
	double* coeff;			///< The coefficients of the polynomial
};

#ifndef __STDC_NO_COMPLEX__
typedef struct cmplx_polynomial cmplx_polynomial;

/**
  * Complex polynomial struct using an array to encapsulate the coefficients.
  */
struct cmplx_polynomial {
	size_t degree;			///< The degree of the polynomial
	double complex* coeff;	///< The complex coefficients of the polynomial
};
#endif

polynomial* poly_get(polynomial* poly_ptr, size_t degree, double coeff[degree+1]);

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
  *			variable in realpolyroots.c. Again, I know it's bad.
  * @param roots An array of doubles to output the root.
  * @return the total number of REAL roots (counting multiplicity).
  */
size_t poly_real_roots(diff_function* poly_func, double x_initial, polynomial * p_ptr, double roots[p_ptr->degree]);

/**
  * Prints a polynomial represented by a polynomial struct onto stdin.
  * @param poly_ptr The polynomial struct to print.
  */
void poly_print(polynomial const* poly_ptr);

#ifndef __STDC_NO_COMPLEX__
/**
  * Divides complex polynomial `dividend` by complex polynomial `divisor` and
  * stores result in `dividend`.
  * @param dividend Pointer to dividend where quotient will be stored.
  * @param divisor Pointer to complex polynomial that divides dividend.
  * @note Quotient is returned in this way because we are not
  *			up to `malloc()`, yet.
  * @note `nr` in `divnr` means "no remainder".
  */
void cmplx_poly_divnr(cmplx_polynomial* dividend, cmplx_polynomial const* divisor);

/**
  * Computes all the COMPLEX roots of a polynomial
  *
  * This was implemented very badly since I wanted to recycle my
  * newton_raphson() prototype. Don't worry, when I learn malloc(),
  * I'll come back to this problem and do it properly
  *
  * @param cmplx_poly_func Pointer to the complex polynomial function.
  * @param z_initial The initial guess for a root.
  * @note This function uses the [Newton-Raphson] method to compute
  *			the roots.
  * @param cp_ptr Pointer to the cmplx_polynomial struct.
  * @note Currently, this is embedded into cmplx_poly_func using a global
  *			variable in cmplxpolyroots.c. Again, I know it's bad.
  * @param roots An array of complex doubles to output the root.
  * @return the total number of COMPLEX roots (counting multiplicity).
  */
size_t poly_cmplx_roots(cmplx_diff_function* cmplx_poly_func, double complex z_initial, cmplx_polynomial* cp_ptr, double complex roots[cp_ptr->degree]);

/**
  * Prints a complex polynomial represented by a cmplx_polynomial
  * struct onto stdin.
  * @param cmpx_poly_ptr The cmplx_polynomial struct to print.
  */
void cmplx_poly_print(cmplx_polynomial const* poly_ptr);
#endif
#endif
