/*
 * Created by: Nelson Cardona
 * Start Date/Time: 23-03-23/21:24
 * End Date/Time: 23-03-23/23:34
 */
#include <errno.h>
#include <time.h>
#include <tgmath.h>
#include <stdlib.h>
#include <stdio.h>

/* Uncomment this to enable DEBUG mode */
//#define DEBUG

#define NSECS_PER_SEC 1000000000

enum { buf_max = 32 };

void merge_dbl(double arr[], size_t lower, size_t mid, size_t upper) {
		size_t arr_size = upper - lower + 1;
		size_t left_index = lower; // Starting index of lower array
		size_t right_index = mid; // Starting index of right array

#ifdef DEBUG
		printf("Merging partition: lower = %zu; mid = %zu; upper = %zu\n", lower, mid, upper);
		/*printf("Sorting partition:\n");
		for (size_t k = lower; k <= upper; ++k)
				printf("arr[%ld] = %.3f\t", k, arr[k]);
		printf("\n");*/
#endif

		/* NOTE: Since we haven't gotten up to pointers - and consequently malloc() - yet,
		 * we leave this array uninitialised as it uses a variable size.
		 */
		double buf[arr_size];
		size_t i = 0; // Buffer index
		do {
#ifdef DEBUG
			printf("Comparing arr[%zu] = %g to arr[%zu] = %g\n", left_index, arr[left_index], right_index, arr[right_index]);
#endif
				if (arr[left_index] <= arr[right_index]) {
						buf[i] = arr[left_index];

						/* NO SIDE-EFFECTS!!! */
						++i;
						++left_index;
				} else {
						buf[i] = arr[right_index];

						/* NO SIDE-EFFECTS!!! */
						++i;
						++right_index;
				}
		} while (left_index <= mid - 1 && right_index <= upper);
#ifdef DEBUG
		printf("buf array is :\n");
		/*for (size_t k = 0; k < i; ++k)
				printf("buf[%ld] = %.3f\t", k, buf[k]);
		printf("\n");*/
#endif

		/* Check whether there are still elements in left/right array */
		if (left_index <= mid - 1) {
				for (size_t j = left_index; j <= mid - 1; ++j) {
						buf[i] = arr[j];
						++i; // NO SIDE-EFFECTS!!!
				}
		} else if (right_index <= upper) {
				for (size_t j = right_index; j <= upper; ++j) {
						buf[i] = arr[j];
						++i; // NO SIDE-EFFECTS!!!
				}
		}

#ifdef DEBUG
		printf("Copying buf back into array\n");
#endif
		/* Copy buf back into arr */
		for (i = 0; i < arr_size; ++i)
				arr[lower+i] = buf[i];
/*#ifdef DEBUG
		printf("Sorted partition:\n");
		for (size_t k = lower; k <= upper; ++k)
				printf("arr[%ld] = %.3f\t", k, arr[k]);
		printf("\n");
#endif*/
}

void mergesort_dbl(double arr[], size_t lower, size_t upper) {
#ifdef DEBUG
		printf("lower: %ld, upper: %ld\n", lower, upper);
#endif
		size_t arr_size = upper - lower + 1; // Establish array size

		/* Handling BASE CASE */
		if (arr_size == 1)
				return;

		/* DOUBLE RECURSION, BBY!!! */
		size_t mid = lower + arr_size/2;
#ifdef DEBUG
		printf("Therefore, arr_size is %ld\n", arr_size);
		printf("Which means midpoint is: %ld\n", mid);
#endif
		mergesort_dbl(arr, lower, mid - 1);
		mergesort_dbl(arr, mid, upper);

		// Actual Merge Sort Alg
		merge_dbl(arr, lower, mid, upper);
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
		mergesort_dbl(list, 0, nitems-1);
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
