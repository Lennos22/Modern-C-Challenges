/* Created by: Nelson Cardona
 * Start Time/Date: 17:39/4-03-23
 * Completion Time/Date: 18:55/4-03-23
 * The CLEANEST DEBUG you'll ever see in your life!!!
 */
#include <stdlib.h>
#include <stdio.h>

/* For strcasecmp() */
#include <strings.h>
/* For strcmp() */
#include <string.h>

/* Uncomment this to enable DEBUG mode */
#define DEBUG

/* Uncomment this to ignore case when sorting */
#define IGNORE_CASE

int cmp(char const* s1, char const* s2) {
#ifdef IGNORE_CASE
		return strcasecmp(s1, s2);
#else
		return strcmp(s1, s2);
#endif
}

void merge_str(char const* arr[], size_t lower, size_t mid, size_t upper) {
		size_t arr_size = upper - lower + 1;
#ifdef DEBUG
		printf("Size of partition: {");
		for (size_t i = lower; i <= upper; ++i) {
				printf("%s", arr[i]);
				if (i < upper)
						printf(", ");
		}
		printf("} is %ld\n", arr_size);
		printf("Calculated midpoint is: %ld\n", mid);
#endif
		size_t left_index = lower;
		size_t right_index = mid + 1;

		/* NOTE: Since we haven't gotten up to pointers - and consequently malloc() - yet,
		 * we leave this array uninitialised since it uses a non-constexpr size.
		 */
		char const* buf[arr_size];
		size_t buf_index = 0;
		do {
				if (cmp(arr[left_index], arr[right_index]) <= 0) {
						buf[buf_index] = arr[left_index];
						++left_index; // NO SIDE-EFFECTS!!!
				} else {
						buf[buf_index] = arr[right_index];
						++right_index; // NO SIDE-EFFECTS!!!
				}
				++buf_index; // NO SIDE-EFFECTS!!!
		} while (left_index <= mid && right_index <= upper);
#ifdef DEBUG
		printf("State of buf after do-while is: {");
		for (size_t i = 0; i < buf_index; i++) {
				printf("%s", buf[i]);
				if (i < buf_index - 1)
						printf(", ");
		}
		printf("}\n");
#endif

		/* Push the rest of the elements onto the buf */
		if (left_index <= mid) {
				for (size_t i = left_index; i <= mid; ++i) {
						buf[buf_index] = arr[i];
						++buf_index; // NO SIDE-EFFECTS!!!
				}
		} else if (right_index <= upper) {
				for (size_t i = right_index; i <= upper; ++i) {
						buf[buf_index] = arr[i];
						++buf_index; // NO SIDE-EFFECTS!!!
				}
		}

		/* Copy buf back into array */
		for (size_t i = 0; i < arr_size; ++i)
				arr[i+lower] = buf[i];
#ifdef DEBUG
		printf("Sorted partition: {");
		for (size_t i = lower; i <= upper; ++i) {
				printf("%s", arr[i]);
				if (i < upper)
						printf(", ");
		}
		printf("}\n\n");
#endif
}

void mergesort_str(char const* arr[], size_t lower, size_t upper) {
		size_t arr_size = upper - lower + 1;
		
		/* Handling BASE CASE */
		if (arr_size == 1)
				return;

		size_t mid = lower + (upper - lower)/2; // Different from mergesort_dbl.c. Should make handling mid indices cleaner!

		/* DOUBLE RECURSION, BBY!!! */
		mergesort_str(arr, lower, mid);
		mergesort_str(arr, mid + 1, upper);

		/* Actual Merge Sort Alg */
		merge_str(arr, lower, mid, upper);
}

int main(int argc, char* argv[argc+1]) {
		size_t arr_size = argc-1;
		char const* arr[argc-1];

		for (int i = 1; i < argc; ++i)
				arr[i-1] = argv[i];

		mergesort_str(arr, 0, arr_size-1);

		printf("Sorted array:\n");
		for (size_t i = 0; i < arr_size; ++i)
				printf("%s\t", arr[i]);
		printf("\n");

		return 0;
}
