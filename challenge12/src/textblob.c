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

#include <assert.h>

/*-----------------*
 * Private Structs *
 *-----------------*/

/**
 * @struct TextBlob
 * Holds a "blob" of text as part of a doubly-linked list.
 */
struct TextBlob {
	char* str;
	size_t len; ///< Holds the number of characters in TextBlob#str, so NOT including null byte.
	TextBlob* prev;
	TextBlob* next;
};

/*-----------------------------*
 * Private Function Prototypes *
 *-----------------------------*/
static size_t getStrLen(char const str[static 1]);
static size_t getStrLen_n(size_t const nChars, char const str[nChars]);

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
		size_t const len = getStrLen(str);

		tbIn->str = malloc(sizeof(char[len + 1]));
		if (!tbIn->str) return (void*) 0;

		strcpy(tbIn->str, str); // We checked the bounds of `str` so `strcpy()` should be safe.
		tbIn->len = len;
		tbIn->prev = (void*) 0;
		tbIn->next = (void*) 0;

		return tbIn;
}

TextBlob* textBlobCtor_n(TextBlob* const tbIn, size_t const nChars, char const str[nChars]) {
		size_t const len = getStrLen_n(nChars, str);

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

	if (tbPtr->str) free(tbPtr->str); // TODO: Consider making a destructor for TextBlob?
	free(tbPtr);
}

TextBlob* textBlobSplit(TextBlob* const tbSrc, size_t const n) {
	if (!tbSrc) return (void*) 0;
	assert(n && n < tbSrc->len);

	TextBlob* tbBack = textBlobNew(tbSrc->str + n);
	if (!tbBack) return (void*) 0;

	char* const s_tmp = malloc(sizeof(char[n + 1]));
	if (!s_tmp) return (void*) 0;
	strncpy(s_tmp, tbSrc->str, n);
	s_tmp[n] = '\0';

	if (!textBlobReplace(tbSrc, s_tmp)) return (void*) 0;
	tbSrc->len = n;

	free(s_tmp);
	
	tbBack->prev = tbSrc;
	if (tbSrc->next) tbSrc->next->prev = tbBack;
	tbBack->next = tbSrc->next;
	tbSrc->next = tbBack;

	return tbSrc;
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

TextBlob* textBlobReplace(TextBlob* const tbPtr, char const newStr[static 1]) {
	size_t const newLen = newStr ? getStrLen(newStr) : 0;

	if (!(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1])))) return (void*) 0;
	strcpy(tbPtr->str, newStr);
	tbPtr->len = newLen;

	return tbPtr;
}

TextBlob* textBlobReplace_n(TextBlob* const tbPtr, size_t const nChars, char const newStr[nChars]) {
	size_t const newLen = getStrLen_n(nChars, newStr);

	if (!(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1])))) return (void*) 0;
	strncpy(tbPtr->str, newStr, newLen);
	tbPtr->str[newLen] = '\0';
	tbPtr->len = newLen;

	return tbPtr;
}

/**************************************************************************************************
 *                                     Private Functions                                          *
 **************************************************************************************************/
static size_t getStrLen(char const str[static 1]) {
	size_t len = 0;

	while(str[len]) ++len;

	return len;
}

static size_t getStrLen_n(size_t const nChars, char const str[nChars]) {
	size_t len = 0;

	while (len < nChars && str[len]) ++len;

	return len;
}
