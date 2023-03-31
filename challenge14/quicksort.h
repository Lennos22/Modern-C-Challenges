/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/16:46
 */
/* @file quicksort.h */
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>

/**
  * Performs a quick sort on an array.
  *
  * Performs a quick sort on the array, @a base, of @a nmemb items that are @a
  * size bytes. @a compar is the comparison criterion for the item type in @a
  * base.
  *
  * @param[in/out]	base	The array to sort.
  * @param[in]		nmemb	The number of items in the array.
  * @param[in]		size	The size (in bytes) of each item.
  * @param[in]		compar	The comparison criterion.
  */
void quicksort(void* base, size_t nmemb, size_t size, int (*compar)(void const*, void const*));

#endif
