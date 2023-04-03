#include "polynomial.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void) {
	polynomial* testpoly = poly_new(2, 0);
	if (!testpoly) {
		fprintf(stderr, "Failed to initialize testpoly.\n");
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}

	printf("Initialized testpoly with degree %zu\n", poly_getdegree(testpoly));

	printf("testpoly elements are:\n");
	poly_print(testpoly);
	putc('\n', stdout);
	poly_delete(testpoly);

	printf("Printing null poly:\n");
	poly_print(0);
	putc('\n', stdout);
}
