/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/12:53
 */
#include "blob.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[argc+1]) {
	if (argc != 2) {
		fprintf(stderr, "Need one non-negative integer argument less than or equal to 6\n");
		return EXIT_FAILURE;
	}
	char text1[strlen("Hello")+1];
	char text2[strlen("There")+1];
	char text3[strlen("Doggy")+1];

	strncpy(text1, "Hello", strlen("Hello")+1);
	strncpy(text2, "There", strlen("There")+1);
	strncpy(text3, "Doggy", strlen("Doggy")+1);

	blob b1 = {0};
	blob b2 = {0};
	blob b3 = {0};

	blob_init(&b1, text1);
	blob_init(&b2, text2);
	blob_init(&b3, text3);

	printf("Printing blobs:\n");
	blob_print(&b1);
	blob_print(&b2);
	blob_print(&b3);
	printf("\n");

	size_t index = strtoull(argv[1], 0, 0);

	printf("Splitting all 3 blobs @ index %zu\n", index);
	blob_split(&b1, index);
	blob_split(&b2, index);
	blob_split(&b3, index);

	/*printf("Printing blobs, again:\n");
	blob_print(&b1);
	blob_print(&b2);
	blob_print(&b3);
	printf("\n");*/

	printf("%s\n", b1.text);
	printf("%s\n", b2.text);
	printf("%s\n", b3.text);

	return EXIT_SUCCESS;
}
