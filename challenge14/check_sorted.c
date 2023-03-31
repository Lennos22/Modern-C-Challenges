/* Code adapted from Challenge 10 */
/* Created by: Nelson Cardona
 * Start Date/Time: 23-03-23/20:48
 * Completion Date/Time: 23-03-23/23:04
 */
/**
  * @file check_sorted.c
  * Checks if a list written in a `.txt` file is sorted.
  */
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare_double(void const* a, void const* b);
int compare_int(void const* a, void const* b);
int compare_str(void const* a, void const* b);

typedef int compare(void const*, void const*);

static compare* cmp_func = compare_double;

enum { buf_max = 32, };

int main(int argc, char* argv[argc-1]) {
	int ret = EXIT_FAILURE;
	for (int i = 1; i < argc; ++i) {
		bool isSorted = true;
		FILE* instream = fopen(argv[i], "r");
		if (instream) {
			char buf[buf_max] = {0};
			size_t nitems = 0;
			if (!fgets(buf, buf_max, instream)) {
				printf("There's less than two items in this \"list\"\n");
				break;
			}
			++nitems;
			double n1 = strtod(buf, 0);
			double n2 = 0;
			while (fgets(buf, buf_max, instream)) {
				n2 = strtod(buf, 0);
				if (cmp_func(&n1, &n2) > 0) {
					isSorted = false;
				}
				n1 = n2;
				++nitems;
			}
			if (isSorted)
				printf("\"%s\" is SORTED. It has %zu items.\n", argv[i], nitems);
			else
				printf("\"%s\" is NOT SORTED. It has %zu items.\n", argv[i], nitems);
			ret = EXIT_SUCCESS;
		} else {
			fprintf(stderr, "Could not open %s: ", argv[i]);
			perror(0);
			errno = 0;
		}
	}
	return ret;
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
	return strcmp(a, b);
}
