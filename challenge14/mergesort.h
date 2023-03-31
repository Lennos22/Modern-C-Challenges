/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/14:11
 */
/** @file mergesort.h */
#ifndef MERGESORT_H
#define MERGESORT_H

#include <stddef.h>

/**
  * Performs a merge sort on an array.
  *
  * Performs a merge sort on the array @a base of @a nmemb items that are @a
  * size bytes. @a compar is used as the comparison criterion for the items in
  * @a base.
  * 
  * @param[in,out]	base	The array to sort.
  * @param[in]		nmemb	The number of items in the array.
  * @param[in]		size	The size (in bytes) of each item.
  * @param[in]		compar	The comparison function.
  */
void mergesort(void* base, size_t nmemb, size_t size, int (*compar)(void const*, void const*));

#endif
