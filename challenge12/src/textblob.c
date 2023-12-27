/**
 * @file textblob.c
 *
 * Contains the implementation for the TextBlob API.
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
#include <stdbool.h>

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
/**
 * Get number of characters in @a str.
 *
 * @param[in] str must be a null-terminated array of chars.
 *
 * @return The number of characters in @a str.
 *
 * @warning A malformed @a str results in U.B.
 * @warning A NULL @a str triggers an assertion and crashes program.
 */
static size_t getStrLen(char const str[static 1]);

/**
 * Bounded - therefore, SAFER - version of getStrLen().
 *
 * @param[in] nChars is the upper bound of characters to be counted in @a str.
 * @param[in] str    is null-terminated and/or at least @a nChars long.
 *
 * @return The number of characters in @a str, up to a maximum of @a nChars.
 *
 * @note @a str can be NULL if AND ONLY IF @a nChars is 0.
 */
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

TextBlob* textBlobCtor(TextBlob* const tbPtr, char const str[static 1]) {
	assert(tbPtr);
	size_t const len = getStrLen(str);

	tbPtr->str = malloc(sizeof(char[len + 1]));
	if (!tbPtr->str) return (void*) 0;

	strcpy(tbPtr->str, str); // We checked the bounds of `str` so `strcpy()` should be safe to use.
	tbPtr->len = len;
	tbPtr->prev = (void*) 0;
	tbPtr->next = (void*) 0;

	return tbPtr;
}

TextBlob* textBlobCtor_n(TextBlob* const tbPtr, size_t const nChars, char const str[nChars]) {
	assert(tbPtr);
	size_t const len = getStrLen_n(nChars, str);

	tbPtr->str = malloc(sizeof(char[len + 1]));
	if (!tbPtr->str) return (void*) 0;

	if (nChars) strncpy(tbPtr->str, str, len);
	tbPtr->str[len] = '\0';
	tbPtr->len = len;
	tbPtr->prev = (void*) 0;
	tbPtr->next = (void*) 0;

	return tbPtr;
}

void textBlobDelete(TextBlob* const tbIn) {
	textBlobDtor(tbIn);
	free(tbIn);
}

void textBlobDtor(TextBlob* const tbIn) {
	if (!tbIn) return;

	free(tbIn->str);
	tbIn->str = (void*) 0;
	tbIn->len = 0;
	tbIn->prev = (void*) 0;
	tbIn->next = (void*) 0;
}

TextBlob* textBlobSplit(TextBlob* const tbSrc, size_t const n) {
	if (!tbSrc) return (void*) 0;
	assert(n && n < tbSrc->len);

	TextBlob* tbBack = textBlobNew(tbSrc->str + n);
	if (!tbBack) return (void*) 0;

	if (!(tbSrc->str = realloc(tbSrc->str, sizeof(char[n + 1]))))
		return (void*) 0;
	tbSrc->str[n] = '\0';
	tbSrc->len = n;

	tbBack->prev = tbSrc;
	if (tbSrc->next) tbSrc->next->prev = tbBack;
	tbBack->next = tbSrc->next;
	tbSrc->next = tbBack;

	return tbSrc;
}

bool textBlobSeparateBy(TextBlob* const tbSrc, char const separator) {
	if (!tbSrc) return false;
	bool res = true;

	for (size_t i = tbSrc->len - 2; i < tbSrc->len - 1; --i) {
		if (tbSrc->str[i] == separator && !textBlobSplit(tbSrc, i + 1))
			res = false;
	}

	return res;
}

TextBlob* textBlobJoin(TextBlob* const tbFront) {
	if (!tbFront) return (void*) 0;

	if (tbFront->next) {
		TextBlob* const tbBack = tbFront->next;

		if (!textBlobAppend(tbFront, tbBack->str)) return (void*) 0;

		tbFront->next = tbBack->next;
		if (tbFront->next)
			tbFront->next->prev = tbFront;

		textBlobDelete(tbBack);
	}

	return tbFront;
}

/*------------------*
 * Helper Functions *
 *------------------*/
char const* textBlobGetStr(const TextBlob* const tbIn) {
	return tbIn ? tbIn->str : (void*) 0;
}

size_t textBlobGetLen(const TextBlob* const tbIn) {
	return tbIn ? tbIn->len : 0;
}

TextBlob* textBlobGetPrev(const TextBlob* const tbIn) {
	return tbIn ? tbIn->prev : (void*) 0;
}

TextBlob* textBlobGetNext(const TextBlob* const tbIn) {
	return tbIn? tbIn->next : (void*) 0;
}

TextBlob* textBlobReplace(TextBlob* const tbPtr, char const newStr[static 1]) {
	if (!tbPtr) return (void*) 0;
	size_t const newLen = getStrLen(newStr);

	if (tbPtr->len != newLen && !(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1]))))
		return (void*) 0;
	strcpy(tbPtr->str, newStr);
	tbPtr->len = newLen;

	return tbPtr;
}

TextBlob* textBlobReplace_n(TextBlob* const tbPtr, size_t const nChars, char const newStr[nChars]) {
	if (!tbPtr) return (void*) 0;
	size_t const newLen = getStrLen_n(nChars, newStr);

	if (tbPtr->len != newLen && !(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1]))))
		return (void*) 0;
	strncpy(tbPtr->str, newStr, newLen);
	tbPtr->str[newLen] = '\0';
	tbPtr->len = newLen;

	return tbPtr;
}

TextBlob* textBlobAppend(TextBlob* const tbPtr, char const str[static 1]) {
	if (!tbPtr) return (void*) 0;
	size_t const newLen = tbPtr->len + getStrLen(str);

	if (newLen > tbPtr->len) {
		if (!(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1]))))
			return (void*) 0;
		strcpy(tbPtr->str + tbPtr->len, str);
		tbPtr->len = newLen;
	}

	return tbPtr;
}

TextBlob* textBlobAppend_n(TextBlob* const tbPtr, size_t const nChars, char const str[nChars]) {
	if (!tbPtr) return (void*) 0;
	size_t const endLen = getStrLen_n(nChars, str);
	size_t const newLen = tbPtr->len + endLen;

	if (newLen > tbPtr->len) {
		if (!(tbPtr->str = realloc(tbPtr->str, sizeof(char[newLen + 1]))))
			return (void*) 0;
		strncpy(tbPtr->str + tbPtr->len, str, endLen);
		tbPtr->str[newLen] = '\0';
		tbPtr->len = newLen;
	}

	return tbPtr;
}

/**************************************************************************************************
 *                                     Private Functions                                          *
 **************************************************************************************************/
static size_t getStrLen(char const str[static 1]) {
	assert(str);
	size_t len = 0;

	while(str[len]) ++len;

	return len;
}

static size_t getStrLen_n(size_t const nChars, char const str[nChars]) {
	// Either str is non-NULL, or nChars is 0.
	assert(str || !nChars);
	size_t len = 0;

	while (len < nChars && str[len]) ++len;

	return len;
}

