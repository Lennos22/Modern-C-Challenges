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
