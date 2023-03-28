/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/16:57
 */
#ifndef NUMERICAL_DERIVATIVE_H
#define NUMERICAL_DERIVATIVE_H

typedef double diff_function(double);

double f(diff_function* F, double x);

#endif
