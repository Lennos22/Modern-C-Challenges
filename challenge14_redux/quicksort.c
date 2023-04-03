/* Adapted from code in Challenge 1 */
/* Created by: Nelson Cardona
 * Creation Date/Time: 31-03-23/16:42
 */
#include "quicksort.h"

#define NDEBUG

#include <stdlib.h>
#ifndef NDEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <assert.h>

static inline void swap(void* p1, void* p2, size_t n);

void quicksort(void* base, size_t nmemb, size_t size, int (*compar)(void const*, void const*)) {
assert(base);
#ifndef NDEBUG
	printf("Sorting %zu items of %zu bytes\n", nmemb, size);
#endif
	if (nmemb <= 1) return;
	unsigned char* left = base;
	unsigned char* right = left + (nmemb-1)*size;
	unsigned char* pivot = left + (nmemb/2)*size;

	swap(pivot, right, size);
	pivot = right;
	right -= size;

#ifndef NDEBUG
	printf("Current state is: left = %p, right = %p, pivot = %p\n", left, right, pivot);
#endif

	for (;;) {
		while (compar(left, pivot) < 0)
			left += size;
		while (compar(right, pivot) > 0)
			right -= size;
		if (left >= right) break;
		swap(left, right, size);
		left += size;
		right -= size;
	}

	swap(left, pivot, size);
	pivot = left;
	left = base;

	size_t l_size = (size_t) (pivot - left)/size;
	size_t r_size = nmemb - l_size - 1;
#ifndef NDEBUG
	printf("Split array into left partition of %zu members and right partition of %zu members\n", l_size, r_size);
	printf("The pointers are: left = %p, right = %p\n\n", left, pivot+size);
#endif
	/* DOUBLE RECURSION, BBY!!! */
	quicksort(base, l_size, size, compar);
	quicksort(pivot+size, r_size, size, compar);
}

static inline void swap(void* p1, void* p2, size_t n) {
assert(dest);
assert(src);
	unsigned char* tmp = malloc(n*sizeof(unsigned char));
	unsigned char* P1 = p1;
	unsigned char* P2 = p2;

	memcpy(tmp, P1, n);
	memcpy(P1, P2, n);
	memcpy(P2, tmp, n);
}
