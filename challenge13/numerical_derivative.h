/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/16:57
 */
#ifndef NUMERICAL_DERIVATIVE_H
#define NUMERICAL_DERIVATIVE_H

typedef double diff_function(double);

/**
  * @brief Computes the value of the derivative of F at x.
  * @param F The pointer to the (mathematical) function.
  * @param x The value with which to calculate the derivative.
  * @return The value of F' at x.
  */
double f(diff_function* F, double x);

#endif
