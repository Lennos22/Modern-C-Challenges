/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/20:16
 */
/**
  * @file polynomial.h
  * Encapsulates polynomial objects and operations.
  */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>

typedef struct polynomial polynomial;

polynomial* poly_init(polynomial* p, size_t degree, double coeff[degree+1]);
polynomial* poly_new(size_t degree, double coeff[degree+1]);
void poly_delete(polynomial* p);
size_t poly_getdegree(polynomial* p);
void poly_print(polynomial* p);

#endif
