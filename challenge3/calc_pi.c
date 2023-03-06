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
#include <stdlib.h>
#include <stdio.h>

/* for sin() */
#include <tgmath.h>
/* for DBL_MIN and DBL_MAX */
#include <float.h>

/* Uncomment this to enable DEBUG mode */
#define DEBUG

/* You can make this as small as you want! The smaller the value,
 * the more precise your approximation can be.
 */
static double const eps = 0x01P-48;
/* Make sure your initial guess isn't on a stationary point.
 * Actually, there shouldn't be ANY stationary points between
 * your initial guess and your target.
 */
static double const x_initial = 3.0;

/* Function you want to differentiate. Feel free to use the
 * functions in tgmath.h. Or, make your own!
 */
double F(double x) {
		return sin(x);
}

/* Using a two-sided differencing method */
double f(double F(double), double x) {
		return (F(x + eps) - F(x - eps)) / (2 * eps);
}

/* The Newton-Raphson method.
 * NOTE: from casual testing in Desmos.com, it seems like the
 * precision of image of the root of F(x) - target corresponds
 * to the precision of the root. At least, in the case of sin(x).
 */
double newton_method(double target, int dec_places) {
		double ans = x_initial;
		/* The negation of dec_places in below computation
		 * requires dec_places to be int instead of size_t!
		 */
		double precision = pow(10, -(dec_places + 1));
#ifdef DEBUG
		printf("Beginning approximation of PI to %d decimal places\n", dec_places);
		printf("The precision must, therefore, be %.*f\n", dec_places + 1, precision);
		printf("Initial guess is: %f\n", ans);
		size_t i = 0; // To keep track of itrs while DEBUGGING
#endif

		while (fabs(F(ans) - target) >= precision) {
				/* NOTE: Technically, the derivative should be
				 * of F(x) - target but since target is
				 * constant, it cancels out!
				 */
				ans = ans - (F(ans) - target)/f(F, ans);
#ifdef DEBUG
				++i;
				printf("Iteration %ld gives us: %.*f\n", i, dec_places, ans);
#endif
		}

		return ans;
}

int main(int argc, char* argv[argc+1]) {
#ifdef DEBUG
		printf("DBL_MIN = %1.4e\n", DBL_MIN);
		printf("DBL_MAX = %1.4e\n", DBL_MAX);
#endif
		if (argc > 2) {
				printf("This program takes one argument: the no. of decimal places of pi to compute\n");
				return EXIT_FAILURE;
		}
		int dec_places = atoi(argv[1]);

		/* Change target to experiment! */
		double result = newton_method(0, dec_places);

		printf("PI to %d decimal places is: %.*f\n", dec_places, dec_places, result);

		return EXIT_SUCCESS;
}
