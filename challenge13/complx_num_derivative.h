/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/17:03
 */
#ifndef COMPLX_NUM_DERIVATIVE_H
#define COMPLX_NUM_DERIVATIVE_H

#ifdef __STDC_NO_COMPLEX__
#error "ERROR: Current C platform does not support complex arithmetic..."
#endif

#include <complex.h>

typedef complex double cmplx_diff_function(complex double);

#endif
