/* TU adapted from code in Challenge 3
 * Creation Date/Time: 28-03-23/16:30
 */

/* Created by: Nelson Cardona
 * Start Time/Date: 13:26/5-03-23
 * Completion Time/Date: 14:47/5-03/23
 * I use Newton-Raphson to approximate PI by a user-specified no.
 * of digits. I chose Newton-Raphson since it also uses the
 * derivative, which I implemented in the previous challenge.
 * Since we haven't gone around to learning headers at this stage,
 * I've opted to just copy-paste the previous challenge's code.
 * 
 * It seems like the maximum precision you can do without the
 * program going haywire is 14 decimal places.
 */
#include "newton_raphson.h"
#include "numerical_derivative.h"

#define NDEBUG

#include <stdio.h>

/* for sin() */
#include <tgmath.h>

static const size_t max_iters = 32;

/* Make sure your initial guess isn't on a stationary point.
 * Actually, there shouldn't be ANY stationary points between
 * your initial guess and your target.
 */
//static double const x_initial = 3.0;

/* The Newton-Raphson method. */
double newton_raphson(diff_function* F, double x_initial, int dec_places) {
		double ans = x_initial;
		/* The negation of dec_places in below computation
		 * requires dec_places to be int instead of size_t!
		 */
		double precision = pow(10, -(dec_places + 1));
		size_t i = 0; // To keep track of iters while

		while (fabs(F(ans)) >= precision && i < max_iters) {
				ans = ans - (F(ans))/f(F, ans);
				++i;
#ifndef NDEBUG
printf("Iteration %ld gives us: %.*f\n", i, dec_places, ans);
#endif
		}

		return ans;
}
