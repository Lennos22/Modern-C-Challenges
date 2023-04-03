/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/14:23
 */
/**
  * @file sort_performance.c
  * Evaluates the performance of my sorting algorithms and qsort().
  */
#include "mergesort.h"
#include "quicksort.h"
#include "time_ops.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int compare_double(void const* a, void const* b);
int compare_int(void const* a, void const* b);
int compare_str(void const* a, void const* b);
void file_open_err(char const filename[static 1]);

typedef int compare(void const*, void const*);

static compare* cmp_func = compare_double;

enum {	buf_max = 32,	};
enum {MERGESORT, QUICKSORT, QSORT};

int main(int argc, char* argv[argc+1]) {
	if (argc < 5) {
		fprintf(stderr, "Program requires 4 arguments: input file, output file, sort code, number of items\n");
		fprintf(stderr, "Sort codes are:\n");
		fprintf(stderr, "MERGESORT = %d\nQUICKSORT = %d\nQSORT = %d\n", MERGESORT, QUICKSORT, QSORT);
		return EXIT_FAILURE;
	}
	FILE* instream = fopen(argv[1], "r");
	if (!instream) file_open_err(argv[1]);

	/* May God have mercy on this RAM */
	/* malloc() IS OUR SAVIOUR!!!!!!! */
	size_t nitems = strtoull(argv[4], 0, 0);
	char buf[buf_max] = {0};
	double* list = malloc(nitems*sizeof(double));
	if (!list) {
		fprintf(stderr, "ERROR: Failed to allocate enough data for %zu items\n", nitems);
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}
	
	for (size_t i = 0; i < nitems; ++i) {
		if (!fgets(buf, buf_max, instream)) {
			fprintf(stderr, "Reached EOF. Only received %zu items.\n", i);
			nitems = i;
			break;
		}
		list[i] = strtod(buf, 0);
	}
	fclose(instream);

	struct timespec begin = {0};
	struct timespec end = {0};
	switch (strtol(argv[3], 0, 0)) {
		case MERGESORT:
			printf("WE MERGIN' BBY!\n");
			timespec_get(&begin, TIME_UTC);
			mergesort(list, nitems, sizeof list[0], cmp_func);
			timespec_get(&end, TIME_UTC);
			printf("Merge sort complete! ");
			break;
		case QUICKSORT:
			printf("WE QUICKSORTIN' BBY!\n");
			timespec_get(&begin, TIME_UTC);
			quicksort(list, nitems, sizeof list[0], cmp_func);
			timespec_get(&end, TIME_UTC);
			printf("Quick sort complete! ");
			break;
		case QSORT:
			printf("qsort()... really?...\n");
			timespec_get(&begin, TIME_UTC);
			qsort(list, nitems, sizeof list[0], cmp_func);
			timespec_get(&end, TIME_UTC);
			printf("Quick sort complete! ");
			break;
		default:
			fprintf(stderr, "ERROR: Invalid sort code. \n");
			fprintf(stderr, "Sort codes are:\n");
			fprintf(stderr, "MERGESORT = %d\nQUICKSORT = %d\nQSORT = %d\n", MERGESORT, QUICKSORT, QSORT);
			return EXIT_FAILURE;
	}
	printf("Sort duration: ");
	timespec_print(timespec_diff(end, begin));
	printf("\n");

	FILE* outstream = fopen(argv[2], "w");
	if (!outstream) file_open_err(argv[2]);

	for (size_t i = 0; i < nitems; ++i)
		fprintf(outstream, "%g\n", list[i]);
	fclose(outstream);
	free(list);

	return EXIT_SUCCESS;
}

int compare_double(void const* a, void const* b) {
	double const* A = a;
	double const* B = b;
	
	if (*A < *B) return -1;
	else if (*A > *B) return 1;
	else return 0;
}

int compare_int(void const* a, void const* b) {
	int const* A = a;
	int const* B = b;

	if (*A < *B) return -1;
	else if (*A > *B) return 1;
	else return 0;
}

int compare_str(void const* a, void const* b) {
	char const* A = a;
	char const* B = b;

	return strcmp(A, B);
}

void file_open_err(char const filename[static 1]) {
	fprintf(stderr, "File \"%s\" could not be opened...\n", filename);
	perror("ERROR: ");
	errno = 0;
	exit(EXIT_FAILURE);
}
