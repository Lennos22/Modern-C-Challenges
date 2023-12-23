/**
  * @file textblob.c
  *
  * Created by Nelson Cardona
  * Creation Date/Time: 23-12-23/17:00
  */
#include "textblob.h"

/*-------------------*
 * C StdLib Includes *
 *-------------------*/
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/*-----------------*
 * Private Structs *
 *-----------------*/
struct TextBlob {
	char* str;
	size_t len;
	TextBlob* prev;
	TextBlob* next;
};

/*-----------------------------*
 * Private Function Prototypes *
 *-----------------------------*/

/**************************************************************************************************
 *                                      Public Functions                                          *
 **************************************************************************************************/
TextBlob* textBlobNew(char const str[static 1]) {
	TextBlob* const tbNew = malloc(sizeof(TextBlob));

	if (tbNew) textBlobCtor(tbNew, str);

	return tbNew;
}

TextBlob* textBlobNew_n(size_t const nChars, char const str[nChars]) {
	TextBlob* const tbNew = malloc(sizeof(TextBlob));

	if (tbNew) textBlobCtor_n(tbNew, nChars, str);

	return tbNew;
}

TextBlob* textBlobCtor(TextBlob* const tbIn, char const str[static 1]) {
		size_t len = 0;
		while (str[len]) ++len;

		tbIn->str = malloc(sizeof(char[len + 1]));
		if (!tbIn->str) return (void*) 0;

		strcpy(tbIn->str, str); // We checked the bounds of `str` so `strcpy()` should be safe.
		tbIn->len = len;
		tbIn->prev = (void*) 0;
		tbIn->next = (void*) 0;

		return tbIn;
}

TextBlob* textBlobCtor_n(TextBlob* const tbIn, size_t const nChars, char const str[nChars]) {
		size_t len = 0;
		while (str[len] && len < nChars) ++len;

		tbIn->str = malloc(sizeof(char[len + 1]));
		if (!tbIn->str) return (void*) 0;

		strncpy(tbIn->str, str, len);
		tbIn->str[len] = '\0';
		tbIn->len = len;
		tbIn->prev = (void*) 0;
		tbIn->next = (void*) 0;

		return tbIn;
}

void textBlobDelete(TextBlob* const tbPtr) {
	if (!tbPtr) return;

	if (tbPtr->str) free(tbPtr->str); // Consider making a destructor for TextBlob?
	free(tbPtr);
}

/*------------------*
 * Helper Functions *
 *------------------*/
char const* textBlobGetStr(const TextBlob* const tbPtr) {
	return tbPtr ? tbPtr->str : (void*) 0;
}

size_t textBlobGetLen(const TextBlob* const tbPtr) {
	return tbPtr ? tbPtr->len : 0;
}

TextBlob* textBlobGetPrev(const TextBlob* const tbPtr) {
	return tbPtr ? tbPtr->prev : (void*) 0;
}

TextBlob* textBlobGetNext(const TextBlob* const tbPtr) {
	return tbPtr ? tbPtr->next : (void*) 0;
}

/**************************************************************************************************
 *                                     Private Functions                                          *
 **************************************************************************************************/

