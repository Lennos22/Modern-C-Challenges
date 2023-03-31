/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/14:23
 */
/**
  * @file sort_performance.c
  * Evaluates the performance of my sorting algorithms and qsort().
  */
#include "mergesort.h"
#include "quicksort.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MERGESORT	0
#define QUICKSORT	1
#define QSORT		2

int compare_double(void const* a, void const* b);
void file_open_err(char const filename[static 1]);

enum {	buf_max = 32,	};

int main(int argc, char* argv[argc+1]) {
	if (argc < 5) {
		fprintf(stderr, "Program requires 4 arguments: input file, output file, number of items, sort code\n");
		fprintf(stderr, "Sort codes are:\n");
		fprintf(stderr, "MERGESORT = 0\nQUICKSORT = 1\nQSORT = 2\n");
		return EXIT_FAILURE;
	}
	FILE* instream = fopen(argv[1], "r");
	if (!instream) file_open_err(argv[1]);

	/* May God have mercy on this RAM */
	size_t nitems = strtoull(argv[3], 0, 0);
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

	switch (strtol(argv[4], 0, 0)) {
		case MERGESORT:
			printf("WE MERGIN' BBY!\n");
			mergesort(list, nitems, sizeof list[0], compare_double);
			break;
		case QUICKSORT:
			printf("WE QUICKSORTIN' BBY!\n");
			quicksort(list, nitems, sizeof list[0], compare_double);
			break;
		default:
			fprintf(stderr, "ERROR: Invalid sort code...\n");
			return EXIT_FAILURE;
	}

	FILE* outstream = fopen(argv[2], "w");
	if (!outstream) file_open_err(argv[2]);

	for (size_t i = 0; i < nitems; ++i)
		fprintf(outstream, "%g\n", list[i]);
	fclose(instream);

	return EXIT_SUCCESS;
}

int compare_double(void const* a, void const* b) {
	double const* A = a;
	double const* B = b;
	
	if (*A < *B) return -1;
	else if (*A > *B) return 1;
	else return 0;
}

void file_open_err(char const filename[static 1]) {
	fprintf(stderr, "File \"%s\" could not be opened...\n", filename);
	perror("ERROR: ");
	errno = 0;
	exit(EXIT_FAILURE);
}
