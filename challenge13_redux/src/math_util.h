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
#ifndef __STDC_NO_COMPLEX__
# include <complex.h>
#endif

double maxd(double a, double b);
bool is_equald(double a, double b, double abs_eps, double rel_eps);
bool is_zerod(double a, double abs_eps);

#ifndef __STDC_NO_COMPLEX__
bool is_equalc(double complex a, double complex b, double abs_eps, double rel_eps);
bool is_zeroc(double complex a, double abs_eps);
void print_cmplx(double complex a);
double complex strtocmplx(char const start[static 1]);
#endif

#endif
