/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/20:06
 */
#include "polynomial.h"
#include "vector.h"
#include "math_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <tgmath.h>

#ifdef NAN
static double poly_newton_raphson(polynomial const* p, double x_init, double abs_eps,
		size_t max_iters);
# ifndef __STDC_NO_COMPLEX__
static double complex cpoly_newton_raphson(complex_polynomial const* cp, double complex z_init,
		double abs_eps, size_t max_iters);
# endif
#endif

/**
  * `struct` representing a polynomial.
  * @note The number of coefficients a polynomial has is one more than its degree.
  */
struct polynomial {
	size_t degree;	///< The degree of the polynomial.
	double* coeff;	///< The coefficients of the polynomial.
};

#ifndef __STDC_NO_COMPLEX__
/**
  * `struct` representing a *complex* polynomial.
  * @note The number of coefficients a polynomial has is one more than its degree.
  */
struct complex_polynomial {
	size_t degree;			///< The degree of the polynomial.
	double complex* coeff;	///< The coefficients of the polynomial.
};
#endif

double const AbsEps = 1E-10;
size_t const MaxIters = 256;

polynomial* poly_init(polynomial* p, size_t degree, double const coeff[degree+1]) {
	if (p) {
		*p = (polynomial) {
			.degree = degree,
			.coeff = malloc(sizeof(double[degree+1])),
		};
		if (coeff) {
			for (size_t i = 0; i <= degree; ++i)
				p->coeff[i] = coeff[i];
		} else {
			for (size_t i = 0; i <= degree; ++i)
				p->coeff[i] = 0;
		}
		if (!p->coeff)
			p = 0;
	}
	return poly_trim(p, AbsEps);
}

polynomial* poly_new(size_t degree, double const coeff[degree+1]) {
	return poly_init(malloc(sizeof(polynomial)), degree, coeff);
}

void poly_delete(polynomial* p) {
	free(p->coeff);
	free(p);
}

polynomial* poly_resize(polynomial* p, size_t new_degree) {
	if (p && p->degree != new_degree) {
		double* new_coeff = realloc(p->coeff, sizeof(double[new_degree+1]));
		if (!new_coeff)
			return 0;
		if (poly_getdegree(p) < new_degree) {
			for (size_t i = p->degree+1; i <= new_degree; ++i)
				new_coeff[i] = 0;
		}
		p->degree = new_degree;
		p->coeff = new_coeff;
	}
	return p;
}

polynomial* poly_copy(polynomial const* src) {
	polynomial* p = poly_new(poly_getdegree(src), src->coeff);
	return p;
}

size_t poly_getdegree(polynomial const* p) {
assert(p);
	return p->degree;
}

double poly_getcoeff(polynomial const* p, size_t n) {
assert(p);
	return (n <= poly_getdegree(p)) ? p->coeff[n] : 0.0;
}

polynomial* poly_trim(polynomial* p, double abs_eps) {
	polynomial* ret = p;
	if (p) {
		size_t p_degree = poly_getdegree(p);
		size_t i;
		for (i = 0; i < p_degree; ++i) {	// No need to check if zeroth degree coeff is zero...
			if (!is_zerod(poly_getcoeff(p, p_degree-i), abs_eps)) break;
		}
		if (i)
			ret = poly_resize(p, p_degree-i);
	}
	return ret;
}

polynomial* poly_add(polynomial* dest, polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = poly_getdegree(dest);
		size_t src_degree = poly_getdegree(src);
		size_t max_degree = (dest_degree > src_degree) ? dest_degree : src_degree;

		if (dest_degree < max_degree) {
			if (!poly_resize(dest, max_degree))
				return 0;
		}
		if (!vector_add(max_degree+1, dest->coeff, src->coeff))
			return 0;
		return poly_trim(dest, AbsEps);
	}
	return 0;
}

polynomial* poly_mult(polynomial* dest, double k) {
	if (dest) {
		if (!vector_mult(poly_getdegree(dest)+1, dest->coeff, k))
			return 0;
	}
	return poly_trim(dest, AbsEps);
}

polynomial* poly_div(polynomial* dest, polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = poly_getdegree(dest);
		size_t src_degree = poly_getdegree(src);
		if (dest_degree < src_degree)
			return 0;
		size_t quot_degree = dest_degree - src_degree;
		double* quot_coeff = malloc((quot_degree+1)*sizeof(double));
		if (!quot_coeff)
			return 0;

		for (size_t i = 0; i <= quot_degree; ++i) {
			quot_coeff[quot_degree-i] = dest->coeff[dest_degree-i]/src->coeff[src_degree];
			for (size_t j = 0; j <= src_degree; ++j) {
				dest->coeff[dest_degree-i-j] -= quot_coeff[quot_degree-i]
					* src->coeff[src_degree-j];
			}
		}

		free(dest->coeff);
		dest->degree = quot_degree;
		dest->coeff = quot_coeff;
		
		return dest;
	}
	return 0;
}

double polynomial_compute(polynomial const* p, double x) {
	double ret = 0.0;
	if (p) {
		for (size_t i = 0; i <= poly_getdegree(p); ++i)
			ret += i ? poly_getcoeff(p, i)*pow(x, i) : poly_getcoeff(p, i);
	}
	return ret;
}

double poly_comp_deriv(polynomial const* p, double x) {
	double ret = 0.0;
	if (p && poly_getdegree(p)) {	// derivative of zero-th degree polynomials is 0!
		for (size_t i = 1; i <= poly_getdegree(p); ++i) {
			ret += (i-1) ? i*poly_getcoeff(p, i)*pow(x, i-1) : poly_getcoeff(p, i);
		}
	}
	return ret;
}

#ifdef NAN
double poly_findroot(polynomial const* p, double x_init) {
	return poly_newton_raphson(p, x_init, AbsEps, MaxIters);
}

void poly_printroots(polynomial const* p, double x_init) {
# ifndef NDEBUG
	printf("Calculating roots of polynomial: ");
	poly_print_func(p);
	putc('\n', stdout);
	printf("Using initial guess of: %g\n", x_init);
# endif
	polynomial* p_cpy = poly_copy(p);
	double roots[poly_getdegree(p)];
	size_t num_roots;

	for (num_roots = 0; num_roots < poly_getdegree(p); ++num_roots) {
		double root = poly_findroot(p_cpy, x_init);

		if (!isfinite(root)) {
			if (!num_roots) {
				printf("Could not find any roots in polynomial. Initial guess may have hit a non-zero "
						"stationary point\n");
				return;
			}
			break;
		}
		polynomial* factor = poly_new(1, (double[2]) { -root, 1 });
		if (!factor) {
			fprintf(stderr, "ERROR: could not allocate memory for factor...\n");
			perror(0);
			errno = 0;
			return;
		}

		roots[num_roots] = root;
		poly_div(p_cpy, factor);
		x_init = root;
# ifndef NDEBUG
		printf("Factor found: ");
		poly_print_func(factor);
		putc('\n', stdout);
		printf("p_cpy is now: ");
		poly_print_func(p_cpy);
		putc('\n', stdout);
		printf("New initial guess is now: %g\n", x_init);
# endif
		poly_delete(factor);
	}
	if (num_roots == 1)
		printf("Found 1 root:\n");
	else
		printf("Found %zu roots:\n", num_roots);
	for (size_t i = 0; i < num_roots; ++i) {
		printf("%g", roots[i]);
		if (i < num_roots-1)
			printf(", ");
	}
	putc('\n', stdout);
	poly_delete(p_cpy);
}
#endif

void poly_print_vec(polynomial const* p) {
	if (p && p->coeff)
		vector_print(poly_getdegree(p)+1, p->coeff);
	else
		printf("Invalid polynomial...");
}

void poly_print_func(polynomial const* p) {
	if (p && p->coeff) {
		size_t p_degree = poly_getdegree(p);
		for (size_t i = 0; i <= p_degree; ++i) {
			double coeff = poly_getcoeff(p, p_degree-i);
			if (!i)
				printf((coeff < 0) ? "-" : "");
			else
				printf((coeff < 0) ? "- " : "+ ");
			printf("%g", fabs(coeff));
			if (i == p_degree) continue;
			putc('x', stdout);
			if (i < p_degree-1)
				printf("^%zu", p_degree-i);
			putc(' ', stdout);
		}

	} else
		fprintf(stderr, "Invalid polynomial...");
}

#ifndef __STDC_NO_COMPLEX__
complex_polynomial* cpoly_init(complex_polynomial* cp, size_t degree,
		double complex const coeff[degree+1]) {
	if (cp) {
		*cp = (complex_polynomial) {
			.degree = degree,
			.coeff = malloc(sizeof(double complex[degree+1])),
		};
		if (!cp->coeff) return 0;
		if (coeff) {
			for (size_t i = 0; i <= degree; ++i)
				cp->coeff[i] = coeff[i];
		} else {
			for (size_t i = 0; i <= degree; ++i)
				cp->coeff[i] = 0;
		}
	}
	return cp;
}

complex_polynomial* cpoly_new(size_t degree, double complex const coeff[degree+1]) {
	return cpoly_init(malloc(sizeof(complex_polynomial)), degree, coeff);
}

void cpoly_delete(complex_polynomial* cp) {
	free(cp->coeff);
	free(cp);
}

complex_polynomial* cpoly_resize(complex_polynomial* cp, size_t new_degree) {
	if (cp && cp->degree != new_degree) {
		double complex* new_coeff = realloc(cp->coeff, sizeof(double complex[new_degree+1]));
		if (!new_coeff)
			return 0;
		if (cpoly_getdegree(cp) < new_degree) {
			for (size_t i = cp->degree+1; i <= new_degree; ++i)
				new_coeff[i] = 0;
		}
		cp->degree = new_degree;
		cp->coeff = new_coeff;
	}
	return cp;
}

complex_polynomial* cpoly_copy(complex_polynomial const* src) {
	complex_polynomial* cp = cpoly_new(cpoly_getdegree(src), src->coeff);
	return cp;
}

size_t cpoly_getdegree(complex_polynomial const* cp) {
assert(cp);
	return cp->degree;
}

double complex cpoly_getcoeff(complex_polynomial const* cp, size_t n) {
assert(cp);
	return (n <= cpoly_getdegree(cp)) ? cp->coeff[n] : 0.0;
}

complex_polynomial* cpoly_trim(complex_polynomial* cp, double abs_eps) {
	complex_polynomial* ret = cp;
	if (cp) {
		size_t cp_degree = cpoly_getdegree(cp);
		size_t i;
		for (i = 0; i < cp_degree; ++i) {	// No need to check if zeroth degree coeff is zero...
			if (!is_zeroc(cpoly_getcoeff(cp, cp_degree-i), abs_eps)) break;
		}
		if (i)
			ret = cpoly_resize(cp, cp_degree-i);
	}
	return ret;
}

complex_polynomial* cpoly_add(complex_polynomial* dest, complex_polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = cpoly_getdegree(dest);
		size_t src_degree = cpoly_getdegree(src);
		size_t max_degree = (dest_degree > src_degree) ? dest_degree : src_degree;

		if (dest_degree < max_degree) {
			if (!cpoly_resize(dest, max_degree))
				return 0;
		}
		if (!cvector_add(max_degree+1, dest->coeff, src->coeff))
			return 0;
		return cpoly_trim(dest, AbsEps);
	}
	return 0;
}

complex_polynomial* cpoly_mult(complex_polynomial* dest, double complex k) {
	if (dest) {
		if (!cvector_mult(cpoly_getdegree(dest)+1, dest->coeff, k))
			return 0;
	}
	return cpoly_trim(dest, AbsEps);
}

complex_polynomial* cpoly_div(complex_polynomial* dest, complex_polynomial const* src) {
	if (dest && src) {
		size_t dest_degree = cpoly_getdegree(dest);
		size_t src_degree = cpoly_getdegree(src);
		if (dest_degree < src_degree)
			return 0;
		size_t quot_degree = dest_degree - src_degree;
		double complex* quot_coeff = malloc((quot_degree+1)*sizeof(double complex));
		if (!quot_coeff)
			return 0;

		for (size_t i = 0; i <= quot_degree; ++i) {
			quot_coeff[quot_degree-i] = dest->coeff[dest_degree-i]/src->coeff[src_degree];
			for (size_t j = 0; j <= src_degree; ++j) {
				dest->coeff[dest_degree-i-j] -= quot_coeff[quot_degree-i]
					* src->coeff[src_degree-j];
			}
		}

		free(dest->coeff);
		dest->degree = quot_degree;
		dest->coeff = quot_coeff;
		
		return dest;
	}
	return 0;
}

double complex complex_polynomial_compute(complex_polynomial const* cp, double complex z) {
	double complex ret = 0.0;
	if (cp) {
		for (size_t i = 0; i <= cpoly_getdegree(cp); ++i)
			ret += i ? cpoly_getcoeff(cp, i)*cpow(z, i) : cpoly_getcoeff(cp, i);
	}
	return ret;
}

double complex cpoly_comp_deriv(complex_polynomial const* cp, double complex z) {
	double complex ret = 0.0;
	if (cp && cpoly_getdegree(cp)) {	// derivative of zero-th degree complex polynomials is 0!
		for (size_t i = 1; i <= cpoly_getdegree(cp); ++i) {
			ret += (i-1) ? i*cpoly_getcoeff(cp, i)*cpow(z, i-1) : cpoly_getcoeff(cp, i);
		}
	}
	return ret;
}

#ifdef NAN
double complex cpoly_findroot(complex_polynomial const* cp, double complex z_init) {
	return cpoly_newton_raphson(cp, z_init, AbsEps, MaxIters);
}

void cpoly_getroots(complex_polynomial const* cp, double complex z_init,
		double complex res[cpoly_getdegree(cp)]) {
# ifndef NDEBUG
	printf("Calculating roots of complex polynomial: ");
	cpoly_print_func(cp);
	putc('\n', stdout);
	printf("Using initial guess of: ");
	print_cmplx(z_init);
	putc('\n', stdout);
# endif
	complex_polynomial* cp_cpy = cpoly_copy(cp);
	double complex roots[cpoly_getdegree(cp)];
	size_t num_roots;

	for (num_roots = 0; num_roots < cpoly_getdegree(cp); ++num_roots) {
		double complex root = cpoly_findroot(cp_cpy, z_init);

		if (!isfinite(creal(root)) || !isfinite(cimag(root))) {
			fprintf(stderr, "ERROR: stopped after %zuth iteration, initial guess may be \n", num_roots);
			fprintf(stderr, "non-zero stationary point or root too large\n");
			break;
		}
		complex_polynomial* factor = cpoly_new(1, (double complex[2]) { -root, 1 });
		if (!factor) {
			fprintf(stderr, "ERROR: could not allocate memory for factor...\n");
			perror(0);
			errno = 0;
			return;
		}

		roots[num_roots] = root;
		cpoly_div(cp_cpy, factor);
		z_init = root;
# ifndef NDEBUG
		printf("Factor found: ");
		cpoly_print_func(factor);
		putc('\n', stdout);
		printf("cp_cpy is now: ");
		cpoly_print_func(cp_cpy);
		putc('\n', stdout);
		printf("New initial guess is now: ");
		print_cmplx(z_init);
		putc('\n', stdout);
# endif
		cpoly_delete(factor);
	}
	cpoly_delete(cp_cpy);
	if (res) {
		for (size_t i = 0; i < cpoly_getdegree(cp); ++i)
			res[i] = roots[i];
	}
}
#endif

void cpoly_print_vec(complex_polynomial const* cp) {
	if (cp && cp->coeff) 
		cvector_print(cpoly_getdegree(cp)+1, cp->coeff);
	else
		fprintf(stderr, "Invalid polynomial...");
}

void cpoly_print_func(complex_polynomial const* p) {
	if (p && p->coeff) {
		size_t cp_degree = cpoly_getdegree(p);
		for (size_t i = 0; i <= cp_degree; ++i) {
			double complex coeff = cpoly_getcoeff(p, cp_degree-i);
			if (i)
				printf(" + ");
			putc('(', stdout);
			print_cmplx(coeff);
			putc(')', stdout);
			if (i == cp_degree) continue;
			putc('z', stdout);
			if (i < cp_degree-1)
				printf("^%zu", cp_degree-i);
		}

	} else
		fprintf(stderr, "Invalid complex polynomial...");
}
#endif

/**************************************************************************************************/
/***									STATIC FUNCTIONS										***/
/**************************************************************************************************/

#ifdef NAN
static double poly_newton_raphson(polynomial const* p, double x_init, double abs_eps,
		size_t max_iters) {
	double ans = x_init;
	size_t i = 0;
	while (!is_zerod(polynomial_compute(p, ans), abs_eps) && i < max_iters) {
		ans -= polynomial_compute(p, ans)/poly_comp_deriv(p, ans);
		++i;
	}
# ifndef NDEBUG
	if (i >= max_iters)
		fprintf(stderr, "Passed max no. of iterations (%zu/%zu)\n", i, max_iters);
	else
		fprintf(stderr, "Zero x = %g reached after %zu iterations!\n", ans, i);
# endif
	return (!p || i >= max_iters) ? NAN : ans;
}

# ifndef __STDC_NO_COMPLEX__
static double complex cpoly_newton_raphson(complex_polynomial const* cp, double complex z_init,
		double abs_eps, size_t max_iters) {
	if (!cp) return NAN;
	double complex ans = z_init;
	size_t i = 0;
	while (!is_zeroc(complex_polynomial_compute(cp, ans), abs_eps) && i < max_iters) {
#  ifndef NDEBUG
		printf("ans = ");
		print_cmplx(ans);
		printf(" cp(ans) = ");
		print_cmplx(complex_polynomial_compute(cp, ans));
		printf(" cp'(ans) = ");
		print_cmplx(cpoly_comp_deriv(cp, ans));
		putc('\n', stdout);
#  endif
		ans -= complex_polynomial_compute(cp, ans)/cpoly_comp_deriv(cp, ans);
		++i;
	}
#  ifndef NDEBUG
	if (i >= max_iters)
		fprintf(stderr, "Passed max no. of iterations (%zu/%zu)\n", i, max_iters);
	else {
		printf("Zero z = ");
		print_cmplx(ans);
		printf(" reached after %zu iterations!\n", i);
	}
#  endif
	return (i >= max_iters) ? NAN : ans;
}
# endif
#endif
