/* Created by Nelson Cardona
 * Creation Date/Time: 09-04-23/22:57
 */
#include "math_util.h"

#include <stdbool.h>
#include <assert.h>
#include <tgmath.h>

double maxd(double a, double b) {
assert(isfinite(a));
assert(isfinite(b));
	return (a > b) ? a : b;
}

bool is_equald(double a, double b, double abs_eps, double rel_eps) {
assert(isfinite(a));
assert(isfinite(b));
	double dist = fabs(a-b);
	if (dist < abs_eps)
		return true;
	return dist < rel_eps*maxd(a, b);
}

bool is_zerod(double a, double abs_eps, double rel_eps) {
assert(isfinite(a));
	return is_equald(a, 0, abs_eps, rel_eps);
}

#ifndef __STDC_NO_COMPLEX__
bool is_equalc(double complex a, double complex b, double abs_eps, double rel_eps) {
assert(isfinite(creal(a)) && isfinite(cimag(a)));
assert(isfinite(creal(b)) && isfinite(cimag(b)));
	return is_equald(creal(a), creal(b), abs_eps, rel_eps)
		&& is_equald(cimag(a), cimag(b), abs_eps, rel_eps);
}

bool is_zeroc(double complex a, double abs_eps, double rel_eps) {
assert(isfinite(creal(a)) && isfinite(cimag(a)));
	return is_zerod(creal(a), abs_eps, rel_eps) && is_zerod(cimag(a), abs_eps, rel_eps);
}
#endif
