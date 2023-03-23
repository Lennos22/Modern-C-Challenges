/* Created by: Nelson Cardona
 * Start Date/Time: 23-03-23/21:38
 * Completion Date/Time: 23-03-23/22:12
 *
 * Creates a randomly generated list of integers from 0 to 1000 (inc.) and saves it in a file.
 */
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc+1]) {
	if (argc < 3) {
		errno = EINVAL;
		perror(0);
		errno = 0;
		fprintf(stderr, "Need two arguments:\n");
		fprintf(stderr, "\t1) Name of text file to store list.\n\t2) Quantity of list items.\n");
		return EXIT_FAILURE;
	}
	FILE* output = fopen(argv[1], "w");
	if (output) {
		srand(time(0));	// Initialise the seed value for rand(), else you'll have same output.
		size_t nitems = strtoull(argv[2], 0, 0);
		for (size_t i = 0; i < nitems; ++i)
			fprintf(output, "%d\n", rand() % 1001);
		fclose(output);
		printf("Generated list of %zu random items in %s\n", nitems, argv[1]);
	} else {
		fprintf(stderr, "Could not open %s: ", argv[1]);
		perror(0);
		errno = 0;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
