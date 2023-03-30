/* Created by Nelson Cardona
 * Creation Date/Time: 30-03-23/13:03
 */
#include <stddef.h>

typedef struct polynomial polynomial;

struct polynomial {
	size_t degree;
	double coeff[];
};

#ifndef __STDC_NO_COMPLEX__
typedef struct cmplx_polynomial cmplx_polynomial;

struct cmplx_polynomial {
	size_t degree;
	double complex coeff[];
};
#endif

polynomial* poly_get(polynomial* poly_pty, size_t degree, double coeff[degree+1]);
void poly_div(polynomial* p_ptr1, polynomial* p_ptr2);
