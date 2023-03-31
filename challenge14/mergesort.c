/* TU adapted from code in Challenge 1 */
/*
 * Created by: Nelson Cardona
 * Creation Date/Time: 31-03-23/13:26
 */
#include "mergesort.h"

#include <stdio.h>
#include <assert.h>

void merge(unsigned char* left, unsigned char* right, size_t nmemb, size_t size, int (*compar)(void const*, void const*));
void byte_cpy(void* dest, void const* src, size_t n);

void mergesort(void* base, size_t nmemb, size_t size, int (*compar)(void const*, void const*)) {
assert(base);
#ifndef NDEBUG
	printf("Sorting %zu members of size %zu\n", nmemb, size);
#endif
	/* Handling BASE CASE */
	if (nmemb <= 1)
			return;
	size_t mid = nmemb/2;
	unsigned char* left = base;
	unsigned char* right = left + mid*size;

#ifndef NDEBUG
	printf("Split array into %zu members on the left and %zu members on the right\n", mid, nmemb-mid); 
	printf("The pointers are: left = %p, right = %p\n\n", left, right);
#endif
	/* DOUBLE RECURSION, BBY!!! */
	mergesort(left, mid, size, compar);
	mergesort(right, nmemb - mid, size, compar);

	// Actual Merge Sort Alg
	merge(left, right, nmemb, size, compar);
}

void merge(unsigned char* left, unsigned char* right, size_t nmemb, size_t size, int (*compar)(void const*, void const*)) {
assert(left < right);
	unsigned char buf[nmemb*size];
	size_t left_size = nmemb/2;
	size_t right_size = nmemb - nmemb/2;
	
	size_t i = 0;
	size_t l_index = 0;
	size_t r_index = 0;
	while (l_index < left_size && r_index < right_size) {
		if (compar(left+l_index*size, right+r_index*size) <= 0) {
			byte_cpy(buf+i*size, left+l_index*size, size);
			++l_index;
		} else {
			byte_cpy(buf+i*size, right+r_index*size, size);
			++r_index;
		}
		++i;
	}

	if (l_index < left_size ) {
assert(r_index == right_size);
		for (size_t j = l_index; j < left_size; ++j) {
			byte_cpy(buf+i*size, left+j*size, size);
			++i;
		}
	} else if (r_index < right_size) {
assert(l_index == left_size);
		for (size_t j = r_index; j < right_size; ++j) {
			byte_cpy(buf+i*size, right+j*size, size);
			++i;
		}
	}

assert(i == nmemb);
	for (size_t j = 0; j < nmemb; ++j)
		byte_cpy(left+j*size, buf+j*size, size);
}

void byte_cpy(void* dest, void const* src, size_t n) {
assert(dest);
assert(src);
	unsigned char* Dest = dest;
	unsigned char const* Src = src;

	for (size_t i = 0; i < n; ++i)
		*(Dest+i) = *(Src+i);
}
