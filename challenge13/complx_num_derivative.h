/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/17:03
 */
/** @file complx_num_derivative.h */
#ifndef COMPLX_NUM_DERIVATIVE_H
#define COMPLX_NUM_DERIVATIVE_H

#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic..."
#endif

#include <complex.h>

typedef double complex cmplx_diff_function(double complex);

/**
  * Computes the value of the complex derivate of F at z.
  * @param F The pointer to the (mathematical) complex function.
  * @note  For those not privy to Complex Analysis, for a complex
  *		function to be complex differentiable at a point z,
  *		it must be BOTH partially-differentiable AND
  *		satisfy the [Cauchy-Riemann relations] at that point. 
  * @param z The value with which to calculate the derivative.
  * @return The value of F' at z.
  * @warning This function will check whether Cauchy-Riemann
  *		relations are satisfied. If NDEBUG is defined in TU,
  *		the function will only give out a warning and continue
  *		operation. Otherwise, it will abort the program.
  *
  * [Cauchy-Riemann relations]: https://en.wikipedia.org/wiki/Cauchy%E2%80%93Riemann_equations
  */
double complex cmplx_f(cmplx_diff_function* F, double complex z);

#endif
