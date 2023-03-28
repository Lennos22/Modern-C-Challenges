/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/17:03
 */
#ifndef COMPLX_NUM_DERIVATIVE_H
#define COMPLX_NUM_DERIVATIVE_H

#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic..."
#endif

#include <complex.h>

typedef complex double cmplx_diff_function(complex double);

/**
  * @brief Computes the value of the complex derivate of F at z.
  * @param F The pointer to the (mathematical) complex function.
  * @note  For those not privy to Complex Analysis, for a complex
  *		function to be complex differentiable at a point z,
  *		it must be BOTH partially-differentiable AND
  *		satisfy the [Cauchy-Riemann relations](https://en.wikipedia.org/wiki/Cauchy%E2%80%93Riemann_equations)
  *		at that point. 
  * @param z The value with which to calculate the derivative.
  * @return The value of f' at z.
  */
double complex cmplx_f(complx_diff_function* F, double complex z);

#endif
