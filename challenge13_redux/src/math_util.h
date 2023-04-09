/* Created by Nelson Cardona
 * Creation Date/Time: 09-04-23/23:01
 */
/**
  * @file math_util.h
  * Small collection of useful general math functions not implemented in `<tgmath.h>`.
  */
#ifndef MATH_UTIL_H
#define MATH_UTIL_H
#include <stdbool.h>

double maxd(double a, double b);
bool is_equald(double a, double b, double abs_eps, double rel_eps);
bool is_zerod(double a, double abs_eps, double rel_eps);

#endif
