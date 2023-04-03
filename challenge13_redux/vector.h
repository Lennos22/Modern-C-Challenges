/* Created by Nelson Cardona
 * Creation Date/Time: 03-04-23/19:50
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

/**
  * Adds two vectors, @a dest and @a src, and stores result in @a dest.
  * @param[in]		nlem	The number of elements in @a dest and @a src.
  * @param[in,out]	dest	The left operand of vector sum and the location of result.
  * @param[in]		src		The right operand of vector sum.
  * @return @a dest if successful. 0 otherwise.
  */
double* vector_add(size_t nelem, double dest[nelem], double const src[nelem]);

/**
  * Multiplies a vector @a dest by scalar @a k.
  *
  * Multiplies vector, @a dest, by scalar, @a k, and stores result back in @a dest. Returns pointer
  * to @a dest back if successful. 0 otherwise.
  *
  * @param[in]		nelem	The number of elements in @a dest.
  * @param[in,out]	dest	The vector array.
  * @param[in]		k		The scalar to multiply @a dest by.
  * @return	Pointer to @a dest if successful. 0 otherwise.
  */
double* vector_mult(size_t nelem, double dest[nelem], double k);

/**
  * Computes the dot product of two vectors, @a v and @a w.
  * @param[in]	nelem	The number of elements in @a v and @a w.
  * @param[in]	v,w		The vectors with which dot product will be computed.
  * @return The dot product of @a v and @a w.
  */
double vector_dotproduct(size_t nelem, double const v[nelem], double const w[nelem]);

#endif