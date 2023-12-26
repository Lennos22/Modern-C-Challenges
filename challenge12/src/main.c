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
#include <stdbool.h>

enum {
	MAX_BUF_LEN = 128,
};

int main(int argc, char* argv[argc + 1]) {
	if (argc < 2) {
		fprintf(stderr, "ERROR: expecting at least one argument...\n");
		return EXIT_FAILURE;
	}
	int errRet = EXIT_FAILURE;

	static const char fMode[] = "r";
	static char s_buf[MAX_BUF_LEN] = {0};
	for (int i = 1; i < argc; ++i) {
		FILE* fp = fopen(argv[i], fMode);
		if (!fp) {
			fprintf(stderr, "ERROR: could not open file \"%s\"\n\n", argv[i]);
			continue;
		}
		TextBlob* tbTxtFile = textBlobNew("");
		if (!tbTxtFile) {
			fprintf(stderr, "ERROR: TextBlob initialisation failed!\n");
			goto CH12_CLEANUP_;
		}
		TextBlob* currTb = tbTxtFile;

		printf("Loading text from file \"%s\"...\n", argv[i]);
		while (fgets(s_buf, sizeof s_buf, fp)) {
			if (!textBlobAppend(tbTxtFile, s_buf)) {
				fprintf(stderr, "ERROR: TextBlob append failed!\n");
				goto CH12_CLEANUP_;
			}
		}

		printf("Separating TextBlob by newline...\n");
		if (!textBlobSeparateBy(tbTxtFile, '\n')) {
			fprintf(stderr, "ERROR: TextBlob separation failed!\n");
			goto CH12_CLEANUP_;
		}

		size_t numLines = 0;

		while (currTb) {
			++numLines;
			printf("|%3zu,%3zu|%s", numLines, textBlobGetLen(currTb) - 1, textBlobGetStr(currTb));
			currTb = textBlobGetNext(currTb);
		}

		printf("There are %zu lines in file \"%s\"\n"
				"Finished processing file \"%s\"\n"
				, numLines, argv[i], argv[i]);

		errRet = EXIT_SUCCESS;

CH12_CLEANUP_: // An expedient solution.
		putc('\n', stdout);
		currTb = tbTxtFile;
		TextBlob* nextTb = textBlobGetNext(currTb);
		textBlobDelete(currTb);
		while (nextTb) {
			currTb = nextTb;
			nextTb = textBlobGetNext(currTb);
			textBlobDelete(currTb);
		}
		fclose(fp);
	}

	if (errRet == EXIT_FAILURE)
		printf("ERROR: none of the arguments were initialised properly\n");

	return errRet;
}

