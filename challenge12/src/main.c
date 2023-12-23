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

int main() {
	TextBlob* tbTest = textBlobNew("Hello, World!");

	if (tbTest)
		printf("`tbTest` initialized!\tLength is: %zu;\tText is: %s\tPrev is: %p\tNext is: %p\n"
				, textBlobGetLen(tbTest)
				, textBlobGetStr(tbTest)
				, textBlobGetPrev(tbTest)
				, textBlobGetNext(tbTest));
	else
		printf("Error initialising `tbTest`\n");

	char const str[] = {'H', 'e', 'l', 'l', '\0', 'o', '!', '\0'};
	TextBlob* tbTest2 = textBlobNew_n(6, str);

	if (tbTest2)
		printf("`tbTest2` initialized!\tLength is: %zu;\tText is: %s\tPrev is: %p\tNext is: %p\n"
				, textBlobGetLen(tbTest2)
				, textBlobGetStr(tbTest2)
				, textBlobGetPrev(tbTest2)
				, textBlobGetNext(tbTest2));
	else
		printf("Error initialising `tbTest2`\n");

	textBlobDelete(tbTest);
	textBlobDelete(tbTest2);
}

