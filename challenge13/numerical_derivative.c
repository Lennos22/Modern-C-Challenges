/* TU adapted from code in Challenge 2
 * Creation Date/Time: 28-03-23/16:56
 */

/* Created by: Nelson Cardona
 * Start Time/Date: 11:39/5-03-23
 * Completion Time/Date: 13:21/5-03/23
 * NOTE: this algorithm is, by no means, perfect. It uses a two-sided
 * differencing method known as "centred differencing" which means
 * that it samples values around an epsilon interval. If your
 * function happens to be non-differentiable within that interval,
 * well... good luck...
 */
#include "numerical_derivative.h"

#include <stdlib.h>
#include <stdio.h>

/* For your bog standard differentiable functions (sin(), exp(), etc.) */
#include <tgmath.h>

/* You can make this as small as you want! */
static double const eps = 0x1P-16;

/* Using a two-sided differencing method */
double f(diff_function F, double x) {
		return (F(x + eps) - F(x - eps)) / (2 * eps);
}
