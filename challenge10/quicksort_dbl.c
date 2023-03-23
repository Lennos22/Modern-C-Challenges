/* Created by: Nelson Cardona
 */
#include <errno.h>
#include <time.h>
#include <tgmath.h>
#include <stdlib.h>
#include <stdio.h>

/* For SIZE_MAX */
#include <stdint.h>

/* Uncomment this to enable DEBUG mode */
//#define DEBUG

#define NSECS_PER_SEC 1000000000

enum { buf_max = 32 };

/* It actually doesn't matter which value is left or right.
 * They get swapped, anyway...
 */
void swp_dbl(double arr[], size_t left, size_t right) {
#ifdef DEBUG
printf("Swapping l_index: %zu w/ r_index: %zu\n", left, right);
#endif
		double swap = arr[left];	// Store left for swap
		arr[left] = arr[right];
		arr[right] = swap;
}

/* NOTE: upper is the upper INDEX. NOT SIZE OF ARRAY!!! */
void quicksort_dbl(double arr[], size_t lower, size_t upper) {
#ifdef DEBUG
		printf("lower: %zu\n", lower);
		printf("upper: %zu\n", upper);
#endif
		
		/* Base case handling. Also prevents arr_size
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
		swp_dbl(arr, pivot, right_index);
		pivot = right_index;
		--right_index;

#ifdef DEBUG
		printf("Swapped pivot w/ right_index:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("arr[%zu] = %.3f\t", i, arr[i]);
		printf("\n");
		printf ("left: %zu, right: %zu, pivot: %zu\n", left_index, right_index, pivot);
#endif

		// Actual QuickSort Alg
		for (;;) {
				// Keep moving left index to right until we reach value larger than pivot
				while (left_index < SIZE_MAX && arr[left_index] < arr[pivot]) {
						++left_index;
				}

				/* Keep moving right index left until we reach value smaller than pivot.
				 * NOTE: right_index is cmped w/ 0 first to prevent seg faults.
				 */
				while (right_index > 0 && arr[right_index] > arr[pivot]) {
						--right_index;
				}

				if (left_index >= right_index)
						break;
				swp_dbl(arr, left_index, right_index);

				// NO SIDE-EFFECTS!!!
				++left_index;
				--right_index;
		}

		// If we pushed pivot to the left, we would swap w/ right_index, instead
		swp_dbl(arr, left_index, pivot);
		pivot = left_index;

#ifdef DEBUG
		printf("Sorted partition:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("arr[%zu] = %.3f\t", i, arr[i]);
		printf("\n");
		printf ("left: %zu, right: %zu, pivot: %zu\n", left_index, right_index, pivot);
#endif

		/* DOUBLE RECURSION, BBY!!!
		 * Also, the conditionals prevent wraparound since indices are of type
		 * size_t
		 */
		if (pivot == 0)
				quicksort_dbl(arr, lower, pivot);
		else
				quicksort_dbl(arr, lower, pivot - 1);
		if (pivot == SIZE_MAX)
				quicksort_dbl(arr, pivot, upper);
		else
				quicksort_dbl(arr, pivot + 1, upper);
}

/* Returns the ABSOLUTE difference between two timespec values.
 * Adapted from Exs 43.
 */
struct timespec timespec_diff(struct timespec ts1, struct timespec ts2) {
	struct timespec result = {
		.tv_nsec = labs(ts1.tv_nsec - ts2.tv_nsec)
	};

#ifdef DEBUG
printf("Initialised result: %zu.%09ld\n", result.tv_sec, result.tv_nsec);
#endif

	if (ts1.tv_sec < ts2.tv_sec) {
#ifdef DEBUG
printf("ts1.tv_sec < ts2.tv_sec\n");
#endif
		result.tv_sec = ts2.tv_sec - ts1.tv_sec;
		if (ts2.tv_nsec < ts1.tv_nsec) {
			--result.tv_sec;
			result.tv_nsec = NSECS_PER_SEC - result.tv_nsec;
		}
	} else if (ts2.tv_sec < ts1.tv_sec) {
#ifdef DEBUG
printf("ts2.tv_sec < ts1.tv_sec\n");
#endif
		result.tv_sec = ts1.tv_sec - ts2.tv_sec;
		if (ts1.tv_nsec < ts2.tv_nsec) {
			--result.tv_sec;
			result.tv_nsec = NSECS_PER_SEC - result.tv_nsec;
		}
	}
	
	return result;
}

void print_timespec(struct timespec ts) {
	printf("%zu.%09lds", ts.tv_sec, ts.tv_nsec);
}

int main(int argc, char* argv[argc+1]) {
	if (argc < 4) {
		errno = EINVAL;
		perror(0);
		errno = 0;
		fprintf(stderr, "Need three arguments:\n");
		fprintf(stderr, "\t1) Name of unsorted list file.");
		fprintf(stderr, "\t2) Quantity of list items.");
		fprintf(stderr, "\t3) Name of output file.\n");
		return EXIT_FAILURE;
	}
	FILE* instream = fopen(argv[1], "r");
	if (instream) {
		printf("\"%s\" successfully opened! Storing values in memory...\n", argv[1]);
		size_t nitems = strtoull(argv[2], 0, 0);
		double list[nitems];
		char buf[buf_max] = {0};
		for (size_t i = 0; i < nitems; ++i) {
			if (!fgets(buf, buf_max, instream)) {
				fprintf(stderr, "Reached EOF. Only received %zu items.\n", i);
				nitems = i;
				break;
			}
			list[i] = strtod(buf, 0);
		}
		fclose(instream);
		printf("Applying merge sort to data...\n");
		/*
		 * BEGIN TIMING HERE!!!
		 */
		struct timespec ts_begin;
		timespec_get(&ts_begin, TIME_UTC);
		quicksort_dbl(list, 0, nitems-1);
		/*
		 * END TIMING HERE!!!
		 */
		struct timespec ts_end;
		timespec_get(&ts_end, TIME_UTC);
		printf("Merge sort complete! Time elapsed: ");
		print_timespec(timespec_diff(ts_end, ts_begin));
		printf("\n");
		FILE* outstream = fopen(argv[3], "w");
		if (outstream) {
			printf("\"%s\" successfully opened! Storing values to file...\n", argv[3]);
			for (size_t i = 0; i < nitems; ++i)
				fprintf(outstream, "%d\n", (signed) list[i]);
			fclose(outstream);
		} else {
			fprintf(stderr, "Could not open %s: ", argv[3]);
			perror(0);
			errno = 0;
			return EXIT_FAILURE;
		}
	} else {
		fprintf(stderr, "Could not open %s: ", argv[1]);
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
