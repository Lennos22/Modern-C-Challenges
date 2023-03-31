/* Created by: Nelson Cardona
 * Start Date/Time: 23-03-23/20:48
 * Completion Date/Time: 23-03-23/23:04
 */
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
				if (n2 < n1) {
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
