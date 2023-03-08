/* Created by: Nelson Cardona
 * Completion Date: 3-03-23*/
#include <stdlib.h>
#include <stdio.h>

/* For SIZE_MAX */
#include <stdint.h>

/* For strcasecmp() */
#include <strings.h>
/* For strcmp() */
#include <string.h>

/* Uncomment this to enable DEBUG mode */
//#define DEBUG

/* Uncomment this to ignore case comparison */
#define IGNORE_CASE

/* It actually doesn't matter which value is left or right.
 * They get swapped, anyway...
 */
void swp_str(char const* arr[], size_t left, size_t right) {
#ifdef DEBUG
printf("Swapping indices: %zu & %zu\n", left, right);
#endif
		char const* swap = arr[left];	// Store left for swap
		arr[left] = arr[right];
		arr[right] = swap;
}

/* DO NOT DO THIS!!!
 * I only did it this way for fun, but you should add some
 * sort of flag to check for ignore-case
 */
int cmp(char const* s1, char const* s2) {
#ifdef IGNORE_CASE
		return strcasecmp(s1, s2);
#else
		return strcmp(s1, s2);
#endif
}

/* NOTE: upper is the upper INDEX. NOT SIZE OF ARRAY!!! */
void quicksort_str(char const* arr[], size_t lower, size_t upper) {
#ifdef DEBUG
		printf("lower: %zu\n", lower);
		printf("upper: %zu\n", upper);
#endif
		
		/* Base case handling. Alse prevents arr_size
		 * from being negative!
		 */
		if (lower >= upper)
				return;

		// Establish size of array
		size_t arr_size = upper - lower + 1;
		// Establish pivots & left/right indices
		size_t pivot = lower + arr_size/2;
		size_t left_index = lower;
		size_t right_index = upper;

#ifdef DEBUG
		printf("Therefore, arr_size is: %zu\n", arr_size);
		printf("Which means pivot is: %zu\n", pivot);
#endif

		// Push pivot to right side of array
		swp_str(arr, pivot, right_index);
		pivot = right_index;
		--right_index;

#ifdef DEBUG
		printf("Swapped pivot w/ right_index:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("arr[%zu] = %s\t", i, arr[i]);
		printf("\n");
		printf ("left: %zu, right: %zu, pivot: %zu\n", left_index, right_index, pivot);
#endif

		// Actual QuickSort Alg
		for (;;) {
				// Keep moving left index to right until we reach value larger than pivot
				while (left_index < SIZE_MAX && cmp(arr[left_index], arr[pivot]) < 0) {
						++left_index;
				}

				/* Keep moving right index left until we reach value smaller than pivot.
				 * NOTE: right_index is cmped w/ 0 to prevent seg faults.
				 */
				while (right_index > 0 && cmp(arr[right_index], arr[pivot]) > 0) {
						--right_index;
				}

				if (left_index >= right_index)
						break;
				swp_str(arr, left_index, right_index);

				// NO SIDE-EFFECTS!!!
				++left_index;
				--right_index;
		}

		// If we pushed pivot to the left, we would swap w/ right_index, instead
		swp_str(arr, left_index, pivot);
		pivot = left_index;

#ifdef DEBUG
		printf("Sorted partition:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("arr[%zu] = %s\t", i, arr[i]);
		printf("\n");
		printf ("left: %zu, right: %zu, pivot: %zu\n", left_index, right_index, pivot);
#endif

		/* DOUBLE RECURSION, BBY!!!
		 * Also, the condionals prevent wraparound since indices are of type
		 * size_t
		 */
		if (pivot == 0)
				quicksort_str(arr, lower, pivot);
		else
				quicksort_str(arr, lower, pivot-1);
		if (pivot == SIZE_MAX)
				quicksort_str(arr, pivot, upper);
		else
				quicksort_str(arr, pivot+1, upper);
}

int main (int argc, char* argv[argc+1]) {
		size_t arr_size = argc-1;
		char const* arr[arr_size];
		
#ifdef DEBUG
		printf("There are %zu arguments\n", arr_size);
#endif
		for (int i = 1; i < argc; ++i) {
#ifdef DEBUG
				printf("Arg %d: ", i);
				printf("%s\n", argv[i]);
#endif
				arr[i-1] = argv[i];
		}

#ifdef DEBUG
		printf("Arguments are good! Starting QuickSort...\n");
#endif
		quicksort_str(arr, 0, arr_size-1);

		printf("Sorted array:\n");
		for (size_t i = 1; i < argc; ++i) {
				printf("%s\t", arr[i-1]);
		}
		printf("\n");
		
		return 0;
}
