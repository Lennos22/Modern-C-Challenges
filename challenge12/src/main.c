/**
 * @file main.c
 *
 * Tests for TextBlob API.
 *
 * There are many Stack Overflow posts about retrieving window size in C, but this one has
 * solutions for both Linux and Windows:
 *     https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
 * 
 * For now, we limit ourselves to Linux platforms. [This Stack Overflow post][SO OS Check]
 * gives an overview of the macros you can check to determine which OS you're compiling in.
 * A full list of macros for most if not all OS'es can be found [here][Predefined Macros].
 *
 * Created by Nelson Cardona
 * Creation Date/Time: 23-12-23/17:45
 *
 * [SO OS Check]: https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
 *     "How do I check OS with a preprocessor directive?"
 * [Predefined Macros]: https://sourceforge.net/p/predef/wiki/OperatingSystems/
 *     "Pre-defined Compiler Macros Wiki"
 */

#if defined (__linux__)
# define PREDEF_LINUX_PLATFORM
#endif

#if defined (__APPLE__) || defined (__MACH__)
# define PREDEF_MAC_OS_PLATFORM
#endif

/* UNIX and BSD OS'es may also contain GNU libc. Will need to confirm...*/

#if !defined (PREDEF_LINUX_PLATFORM) && !defined (PREDEF_MAC_OS_PLATFORM_)
# error "Current platform does not support GNU libc..."
#endif

/*------------------*
 * Project Includes *
 *------------------*/
#include "textblob.h"

/*-----------------------*
 * GNU libc API Includes *
 *-----------------------*/ 
#include <sys/ioctl.h>
#include <unistd.h>

/*-------------------*
 * C StdLib Includes *
 *-------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#define stringify(s)       # s
#define macro_stringify(s) stringify(s)

#define SECTION_OUT_BANNER_START \
========================================START-OF-SECTION============================================

#define SECTION_OUT_BANNER_END \
=========================================END-OF-SECTION=============================================

#define SECTION_OUT_START "START-OF-SECTION"
#define SECTION_OUT_END   "END-OF-SECTION"

#define BANNER_CHAR       '='

enum {
	MAX_BUF_LEN = 128,
};

/*-----------------------------*
 * Private Function Prototypes *
 *-----------------------------*/
size_t printBlobList(TextBlob* const head, bool hasLSwitch, bool hasWinsize);
void printStartBanner(struct winsize const* const w);
void printEndBanner(struct winsize const* const w);
void printHelp();

int main(int argc, char* argv[argc + 1]) {
	static char const lSwitch[] = "-l";
	static char const winsizeSwitch[] = "--winsize";
	static char const wsSwitch[] = "-ws";
	static char const helpSwitch[] = "--help";

	int errRet = EXIT_FAILURE;
	size_t fargs = 0;
	int lSwitchIdx = 0;
	int winsizeIdx = 0;
	int helpIdx = 0;

	/*--- Find Switches ---*/
	for (int i = 1; i < argc; ++i) {
		if (!lSwitchIdx && !strcmp(argv[i], lSwitch)) {
			printf("Found switch \"%s\" @ arg %d!\n", lSwitch, i);
			lSwitchIdx = i;
		} else if (!winsizeIdx
				&& (!strcmp(argv[i], winsizeSwitch) || !strcmp(argv[i], wsSwitch))) {
			struct winsize w = {0};
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			printf("Found switch \"%s\" @ arg %d!\n"
					"lines = %hu\n"
					"columns = %hu\n"
					, winsizeSwitch, i, w.ws_row, w.ws_col);
			winsizeIdx = i;
		} else if (!helpIdx && !strcmp(argv[i], helpSwitch)) helpIdx = i;
		else ++fargs;
	}
	if (lSwitchIdx || winsizeIdx) putc('\n', stdout);

	/*--- Check Valid Args ---*/
	if (!fargs || helpIdx) {
		printHelp();
		return EXIT_SUCCESS;
	}

	/*--- Process Args ---*/
	static const char fMode[] = "r";
	static char s_buf[MAX_BUF_LEN] = {0};
	for (int i = 1; i < argc; ++i) {
		if (i == lSwitchIdx || i == winsizeIdx || i == helpIdx) continue;
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

		printf("File processing complete! Output is:\n\n");

		size_t numLines = printBlobList(tbTxtFile, lSwitchIdx, winsizeIdx);

		printf("\nThere are %zu lines in file \"%s\"\n"
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
		fprintf(stderr, "ERROR: none of the arguments were initialised properly\n");

	return errRet;
}

size_t printBlobList(TextBlob* const head, bool hasLSwitch, bool hasWinsize) {
	size_t numLines = 0;
	TextBlob* currTb = head;

	struct winsize w = {0};
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size_t rowsLeft = w.ws_row;

	assert (rowsLeft);
	printStartBanner(&w);
	// Put extra line after/before start/end banner in case terminal removes it when resizing.
	putc('\n', stdout);
	while (currTb) {
		++numLines;
		// Still want to count `numLines` even if out of row space in terminal.
		if (hasWinsize && (!rowsLeft || rowsLeft > w.ws_row)) {
			currTb = textBlobGetNext(currTb);
			continue;
		}
		int nPrint = 0;
		char const* const str = textBlobGetStr(currTb);
		/*
		 * DIRTY VLA. Very slim chance that tmpSz becomes too large for stack as I can not imagine
		 * window width on any machine to be anywhere near the order of magnitude of `size_t`.
		 *
		 * Unless, you run a toaster...
		 */
		size_t const tmpSz = textBlobGetLen(currTb) + (hasLSwitch ? 16 : 1);
		char s_tmp[tmpSz]; 
		size_t const len = textBlobGetLen(currTb)
			- ((str[textBlobGetLen(currTb) - 1] == '\n') ? 1 : 0);

		if (hasLSwitch)
			nPrint = snprintf(s_tmp, tmpSz, "|%3zu,%3zu|%s", numLines, len, str);
		else
			nPrint = snprintf(s_tmp, tmpSz, "%s", str);

		bool hasNewLine = len < textBlobGetLen(currTb);

		if (hasWinsize) {
			// EOL being the only character in line is an edge case that muct be handled. Hence, the check
			// for `nPrint > 1`.
			if (nPrint > 1 && hasNewLine) --nPrint;
			size_t const numLines = nPrint / w.ws_col + ((nPrint % w.ws_col) ? 1 : 0);
			if (numLines > rowsLeft) {
				nPrint = w.ws_row * (numLines - rowsLeft);
				s_tmp[nPrint] = '\0';
				hasNewLine = s_tmp[nPrint - 1] == '\n';
			}
			rowsLeft -= numLines;
		}
		printf("%s", s_tmp);
		if (!hasNewLine) putc('\n', stdout);

		currTb = textBlobGetNext(currTb);
	}
	putc('\n', stdout);
	printEndBanner(&w);

	return numLines;
}

void printStartBanner(struct winsize const* const w) {
	if (!w) {
		puts(macro_stringify(SECTION_OUT_BANNER_START)); 
		return;
	}
	size_t i = 0;
	size_t numBannerChars = w->ws_col - (sizeof SECTION_OUT_START) + 1; 
	char bannerStart[w->ws_col + 1];

	for (; i < numBannerChars / 2; ++i) bannerStart[i] = BANNER_CHAR;
	sprintf(bannerStart + (numBannerChars / 2), "%s", SECTION_OUT_START);
	for (i += (sizeof SECTION_OUT_START) - 1; i < w->ws_col; ++i) bannerStart[i] = BANNER_CHAR;
	bannerStart[w->ws_col] = '\0';

	puts(bannerStart);
}

void printEndBanner(struct winsize const* const w) {
	if (!w) {
		puts(macro_stringify(SECTION_OUT_BANNER_END)); 
		return;
	}
	size_t i = 0;
	size_t numBannerChars = w->ws_col - (sizeof SECTION_OUT_END) + 1; 
	char bannerEnd[w->ws_col + 1];

	for (; i < numBannerChars / 2; ++i) bannerEnd[i] = BANNER_CHAR;
	sprintf(bannerEnd + (numBannerChars / 2), "%s", SECTION_OUT_END);
	for (i += (sizeof SECTION_OUT_END) - 1; i < w->ws_col; ++i) bannerEnd[i] = BANNER_CHAR;
	bannerEnd[w->ws_col] = '\0';

	puts(bannerEnd);
}

void printHelp() {
	printf("Usage: textprocessor [OPTIONS]... [FILE]...\n"
			"This text processor prints text from a given file(s) line by line.\n"
			"Options can be put in any order. E.g. './textprocessor Makefile -l' works\n"
			"as well as './textprocessor -l Makefile'.\n"
			"Specifying an option muliple times will treat subsequent duplicates as file args.\n"
			"\n"
			"Options:\n"
			"\t-l             verbose output: include line no. + no. of chars on each line\n"
			"\t-ws, --winsize limit amount of text printed to current size of output window\n"
			"\t     --help    get help text\n"
			"\n"
			"Very limited program that is only verified to work in Linux and Mac terminal\n"
			"environments. I tried my best...\n");
}

