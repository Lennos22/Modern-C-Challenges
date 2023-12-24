/**
  * @file main.c
  *
  * Created by Nelson Cardona
  * Creation Date/Time: 23-12-23/17:45
  *
  * Tests for TextBlob API.
  */

/*------------------*
 * Project Includes *
 *------------------*/
#include "textblob.h"

/*-------------------*
 * C StdLib Includes *
 *-------------------*/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc + 1]) {
	if (argc < 2) {
		fprintf(stderr, "ERROR: expecting at least one argument...\n");
		return EXIT_FAILURE;
	}
	if (argc == 2) {
		TextBlob* tbInput = textBlobNew(argv[1]);
		printf("Text input is: %s - len: %zu\n", textBlobGetStr(tbInput), textBlobGetLen(tbInput));
	}
	int errRet = EXIT_FAILURE;

	for (int i = 1; i < argc; ++i) {
		TextBlob* tbInput = textBlobNew(argv[i]);
		if (!tbInput) {
			fprintf(stderr, "ERROR: could not initialise argument %d\n", i);
			continue;
		}
		errRet = EXIT_SUCCESS; 

		char const* str = textBlobGetStr(tbInput);
		size_t len = textBlobGetLen(tbInput);

		printf("Argument %d is: \"%s\", length: %zu\n", i, str, len); 

		printf("Splitting blob in half...\n");
		textBlobSplit(tbInput, len/2);

		str = textBlobGetStr(tbInput);
		len = textBlobGetLen(tbInput);
		printf("Front of blob is: \"%s\", length: %zu\n", str, len);

		str = textBlobGetStr(textBlobGetNext(tbInput));
		len = textBlobGetLen(textBlobGetNext(tbInput));
		printf("Back of blob is: \"%s\", length: %zu\n", str, len);

		printf("Replacing blob with \"wonky\"...\n");
		textBlobReplace(tbInput, "wonky");

		str = textBlobGetStr(tbInput);
		len = textBlobGetLen(tbInput);
		printf("Front of blob is now: \"%s\", length: %zu\n", str, len);

		str = textBlobGetStr(textBlobGetNext(tbInput));
		len = textBlobGetLen(textBlobGetNext(tbInput));
		printf("Back of blob is still: \"%s\", length: %zu\n\n", str, len);

		textBlobDelete(textBlobGetNext(tbInput));
		textBlobDelete(tbInput);
	}

	if (errRet == EXIT_FAILURE)
		printf("ERROR: none of the arguments were initialised properly\n");

	return errRet;
}

