/* Created by Nelson Cardona
 * Creatione Date/Time: 03-04-23/19:38
 */
#include "vector.h"

#include <stddef.h>

double* vector_add(size_t nelem, double dest[nelem], double const src[nelem]) {
	double* ret = 0;
	if (dest && src) {
		ret = dest;
		for (size_t i = 0; i < nelem; ++i)
			dest[nelem] += src[nelem];
	}
	return ret;
}

double* vector_mult(size_t nelem, double dest[nelem], double k) {
	double* ret = 0;
	if (dest) {
		ret = dest;
		for (size_t i = 0; i < nelem; ++i)
			dest[nelem] *= k;
	}
	return ret;
}

double vector_dotproduct(size_t nelem, double const v[nelem], double const w[nelem]) {
	double ret = 0;
	if (v && w) {
		for (size_t i = 0; i < nelem; ++i)
			ret += v[i]*w[i];
	}
	return ret;
}
