/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/20:16
 */
/**
  * @file polynomial.h
  * Encapsulates polynomial objects and operations.
  */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>
#include <complex.h>

typedef struct polynomial polynomial;

#ifndef __STDC_NO_COMPLEX__
typedef struct complex_polynomial complex_polynomial;
#endif

/**
  * Initialize polynomial object @p.
  * @param[in,out]	p	Pointer to the polynomial object.
  * @param[in]		degree	The degree of the new polynomial object.
  * @param[in]		coeff	The coefficients of the new polynomial object.
  *	@note	If coeff is NULL, then polynomial coefficients will be **zero initialized**.
  * @return	Pointer to polynomial (i.e. @a p) if initialization was successful. 0, otherwise.
  */
polynomial* poly_init(polynomial* p, size_t degree, double const coeff[degree+1]);

/**
  * Generate a new polynomial object and initialize it.
  * @param[in]	degree	The degree of the new polynomial object.
  * @param[in]	coeff	The coefficients of the new polynomial object.
  * @note	If coeff is NULL, then polynomial coefficients will be **zero initialized**.
  * @return	Pointer to new polynomial if initialization was successful. 0, otherwise.
  */
polynomial* poly_new(size_t degree, double const coeff[degree+1]);

/**
  * Deletes the polynomial object @a p.
  * @param[in]	p	Pointer to the polynomial object.
  * @note		If @a p is NULL, then nothing happens.
  * @warning	If polynomial does not follow the same input rules as `malloc()`, then **BAD**
  *				things will happen...
  */
void poly_delete(polynomial* p);

/**
  * Resizes a polynomial object to degree @a new_degree and zero inits new coefficients.
  * @param[in,out]	p			Pointer to polynomial object.
  * @param[in]		new_degree	New degree of @a p.
  * @return Returns back the pointer @a p. 0, if reallocation fails.
  * @note	If @a new_degree is smaller than @a p 's degree, higher degrees will be truncated. If
  *			@a new_degree is larger, then higher degree will be **zero initialized**. If @a
  *			new_degree is equal, nothing happens.
  */
polynomial* poly_resize(polynomial* p, size_t new_degree);

/**
  * Copies a polynomial @a src.
  * @param[in]	src	Pointer to the polynomial object.
  * @return	Pointer to the copy of @a src if successful. 0, otherwise.
  */
polynomial* poly_copy(polynomial const* src);

/**
  * Gets the degree of polynomial @a p.
  * @param[in]	p	Pointer to the polynomial object.
  * @return	The degree of polynomial @a p.
  */
size_t poly_getdegree(polynomial const* p);

/**
  * Gets the value of the @a n th coefficient of polynomial @a p.
  * @param[in]	p	Pointer to the polynomial object.
  * @param[in]	n	The position of the coefficient to be received.
  * @return	The @a n th coefficient of polynomial @a p. If n is larger than the degree of @a p,
  *			then it will return 0.
  */
double poly_getcoeff(polynomial const* p, size_t n);

/**
  * Determines the actual degree of polynomial @a p and resizes it accordingly.
  *
  * Uses @a abs_eps and @a rel_eps to determine whether a coefficient is effectively zero.
  */
polynomial* poly_trim(polynomial* p, double abs_eps);

/**
  * Adds two polynomials, @a dest and @a src, together and stores result in @a dest.size
  * @param[in,out]	dest	Pointer to polynomial that holds result of addition.
  * @param[in]		src		Pointer to polynomial that will be added to @a dest.
  * @return	@a dest if addition was successful. 0, otherwise.
  */
polynomial* poly_add(polynomial* dest, polynomial const* src);

/**
  * Multiplies polynomial @a dest by scalar @a k and stores result back into @a dest.
  * @param[in,out]	dest	Pointer to polynomial object that will also store result.
  * @param[in]		k		Scalar to multiply @a dest by.
  * @return	Returns @a dest if successful. 0, otherwise.
  */
polynomial* poly_mult(polynomial* dest, double k);

/**
  * Divides polynomial @a dest by @a src and stores result back into @a dest.
  * @note This division algorithm output is similar to integer division where the remainder is
  *			*truncated*.
  * @param[in,out]	dest	Pointer to dividend.
  * @param[in]		src		Pointer to divisor.
  * @return	Returns @a dest if successful. 0, otherwise.
  */
polynomial* poly_div(polynomial* dest, polynomial const* src);

/**
  * Computes the polynomial @a p at @a x.
  * @param[in]	p	Pointer to the polynomial object.
  * @param[in]	x	The input to polynomial @a p.
  * @return	The value of the polynomial @a p at @a x. Will return 0 if p is NULL.
  */
double polynomial_compute(polynomial const* p, double x);

/**
  * Computes the derivative of polynomial @a p at @a x.
  * @param[in]	p	Pointer to the polynomial object.
  * @param[in]	x	The input to polynomial @a p.
  * @return	The value of the derivative of polynomial @a p at @a x. Will return 0 if p is NULL.
  */
double poly_comp_deriv(polynomial const* p, double x);

/**
  * Finds a root of polynomial @a p based on an initial guess @a x.
  * @note uses the [Newton-Raphson method] to calculate a root of @a p. This method requires an
  *			initial guess, specified by @a x_init.
  * @param[in]	p		Pointer to the polynomial object.
  * @param[in]	x_init	Initial guess for root of @a p.
  * @return	A root closest to @a x_init. If unable to find root, will return NAN.
  *
  * [newton-raphson method]: https://en.wikipedia.org/wiki/Newton%27s_method
  */
double poly_findroot(polynomial const* p, double x_init);

/**
  * Prints out all the *real* roots of polynomial @a p.
  * @note uses the [Newton-Raphson method] to calculate the roots of @a p. This method requires an
  *			initial guess, specified by @a x_init.
  * @param[in]	p		Pointer to the polynomial object.
  * @param[in]	x_init	Initial guess for root of @a p.
  *
  * [newton-raphson method]: https://en.wikipedia.org/wiki/Newton%27s_method
  */
void poly_printroots(polynomial const* p, double x_init);

/**
  * Prints the coefficients of polynomial @a p in vector form.
  * @param[in]	p	Pointer to the polynomial object.
  */
void poly_print_vec(polynomial const* p);

/**
  * Prints the polynomial @a p in function form.
  * @param[in]	p	Pointer to the polynomial object.
  */
void poly_print_func(polynomial const* p);

#ifndef __STDC_NO_COMPLEX__
complex_polynomial* cpoly_init(complex_polynomial* cp, size_t degree,
		double complex const coeff[degree+1]);
complex_polynomial* cpoly_new(size_t degree, double complex const coeff[degree+1]);
void cpoly_delete(complex_polynomial* cp);
complex_polynomial* cpoly_resize(complex_polynomial* cp, size_t new_degree);
complex_polynomial* cpoly_copy(complex_polynomial const* src);
size_t cpoly_getdegree(complex_polynomial const* cp);
double complex cpoly_getcoeff(complex_polynomial const* cp, size_t n);
complex_polynomial* cpoly_trim(complex_polynomial* cp, double abs_eps);
complex_polynomial* cpoly_add(complex_polynomial* dest, complex_polynomial const* src);
complex_polynomial* cpoly_mult(complex_polynomial* dest, double complex k);
complex_polynomial* cpoly_div(complex_polynomial* dest, complex_polynomial const* src);
double complex complex_polynomial_compute(complex_polynomial const* cp, double complex z);
double complex cpoly_comp_deriv(complex_polynomial const* cp, double complex z);
double complex cpoly_findroot(complex_polynomial const* cp, double complex z_init);
void cpoly_getroots(complex_polynomial const* cp, double complex z_init,
		double complex res[cpoly_getdegree(cp)]);
void cpoly_print_vec(complex_polynomial const* cp);
void cpoly_print_func(complex_polynomial const* cp);
#endif

#endif
