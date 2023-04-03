/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/17:22
 */
/** @file byte_ops.h */
#ifndef BYTE_OPS_H
#define BYTE_OPS_H

#include <stddef.h>

/**
  * Swaps @a n bytes of @a p1 with @a n bytes of @a p2.
  * @param[in,out]	p1,p2	Pointers whose values will be swapped.
  * @param[in]		n		Number of bytes to swap.
  */
void byte_swp(void* p1, void* p2, size_t n);

/**
  * Copies first @a n bytes of @a src into first @a n bytes of @a dest.
  * @param[out]	dest	Pointer to copy @a n bytes into.
  * @param[in]	src		Pointer that will be copied.
  * @param[in]	n		Number of bytes to copy.
  */
void byte_cpy(void* dest, void const* src, size_t n);

#endif
