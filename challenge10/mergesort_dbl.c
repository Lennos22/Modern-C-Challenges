/*
 * Created by: Nelson Cardona
 * Start Date/Time: 23-03-23/21:24
 * End Date/Time: 4-03-23/17:38
 */
#include <stdlib.h>
#include <stdio.h>

/* Uncomment this to enable DEBUG mode */
//#define DEBUG

void merge_dbl(double arr[], size_t lower, size_t mid, size_t upper) {
		size_t arr_size = upper - lower + 1;
		size_t left_index = lower; // Starting index of lower array
		size_t right_index = mid; // Starting index of right array

#ifdef DEBUG
		printf("Sorting partition:\n");
		for (size_t k = lower; k <= upper; ++k)
				printf("arr[%ld] = %.3f\t", k, arr[k]);
		printf("\n");
#endif

		/* NOTE: Since we haven't gotten up to pointers - and consequently malloc() - yet,
		 * we leave this array uninitialised as it uses a variable size.
		 */
		double buf[arr_size];
		size_t i = 0; // Buffer index
		do {
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
		for (size_t k = 0; k < i; ++k)
				printf("buf[%ld] = %.3f\t", k, buf[k]);
		printf("\n");
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

		/* Copy buf back into arr */
		for (i = 0; i < arr_size; ++i)
				arr[lower+i] = buf[i];
#ifdef DEBUG
		printf("Sorted partition:\n");
		for (size_t k = lower; k <= upper; ++k)
				printf("arr[%ld] = %.3f\t", k, arr[k]);
		printf("\n");
#endif
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

int main(int argc, char* argv[argc+1]) {
		size_t arr_size = argc-1; // Remember, 1st arg is prog name; second is '\0'
		double arr[arr_size];

#ifdef DEBUG
		printf("There are %ld arguments\n", arr_size);
#endif

		for (int i = 1; i < argc; ++i) 
				arr[i-1] = strtod(argv[i], 0);

#ifdef DEBUG
		printf("Arguments are good! Starting Merge Sort...\n");
#endif

		mergesort_dbl(arr, 0, arr_size-1);

		printf("Sorted array:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("%.3f\t", arr[i]);
		printf("\n");

		return 0;
}
