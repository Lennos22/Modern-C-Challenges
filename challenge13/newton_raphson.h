/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/16:33
 */
/** @file newton_raphson.h */
#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H
#include "numerical_derivative.h"

#ifndef __STDC_NO_COMPLEX__
#include <complex.h>
#endif

/**
  * Employs the [Newton-Raphson method] to compute a root of a function near
  * x_initial.
  * @param F Function to calculate root.
  * @param x_initial The initial guess of the location of a root.
  * @param dec_places The number of decimal places to calculate root up to.
  *
  * [newton-raphson method]: https://en.wikipedia.org/wiki/Newton%27s_method
  */
double newton_raphson(diff_function* F, double x_initial, int dec_places);

#ifndef __STDC_NO_COMPLEX__
double complex cmpls_newton_raphson(cmplx_diff_function* F, double complex z_initial, int dec_places);
#endif

#endif
