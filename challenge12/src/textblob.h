/**
  * @file textblob.h
  *
  * Created by Nelson Cardona
  * Creation Date/Time: 23-12-23/17:00
  *
  * Store text in a doubly-linked list of "blobs".
  */
#ifndef TEXTBLOB_H_
#define TEXTBLOB_H_

/*-------------------*
 * C StdLib Includes *
 *-------------------*/
#include <stddef.h>

/*-----------------*
 * Public Typedefs *
 *-----------------*/
typedef struct TextBlob TextBlob;

/**************************************************************************************************
 *                                      Public Functions                                          *
 **************************************************************************************************/

/**
 * Creates a new TextBlob of the given string, @a str.
 *
 * @param[in] str must be null-terminated.
 * 
 * @warning Passing an improper string (e.g. not null-terminated) is U.B.
 *
 * @return Pointer to new TextBlob, otherwise NULL, if initialisation fails.
 */
TextBlob* textBlobNew(char const str[static 1]);

/**
 * Bounded - therefore, SAFER - version of textBlobNew().
 *
 * It limits the number of characters in a TextBlob to @a nChars. If @a str is null-terminated
 * before @a nChars, the true length of the TextBlob will be reflected, accordingly. Therefore,
 * do not expect @a nChars to be the final length.
 *
 * @param[in] nChars is the upper limit of TextBlob string.
 * @param[in]      str    is null-terminated and/or at least @a nChars long.
 *
 * @return Pointer to new TextBlob, otherwise NULL, if initialisation fails.
 */
TextBlob* textBlobNew_n(size_t const nChars, char const str[nChars]);

/**
 * Constructs the TextBlob specified by @a tbPtr using a NULL-TERMINATED string, @a str.
 *
 * @param[in, out] tbPtr should be uninitialised. Otherwise, you will have problems with memory
 *                       management.
 * @param[in]      str   must be null-terminated.
 * @see            textBlobDelete().
 *
 * @warning Passing an improper string (e.g. not null-terminated) is U.B.
 *
 * @return @a tbPtr if construction was successful. Otherwise, NULL.
 *
 * @note If @a tbPtr is NULL, then NULL will simply be returned.
 */
TextBlob* textBlobCtor(TextBlob* const tbPtr, char const str[static 1]);

/**
 * Bounded - therefore, SAFER - version of textBlobCtor().
 *
 * It limits the number of characters in @a tbPtr to @a nChars. If @a str is null-terminated
 * before @a nChars, the true length will be reflected, accordingly. Therefore, do not expect @a
 * nChars to be the final length of %a tbPtr.
 *
 * @param[in, out] tbPtr  should be uninitialised. Otherwise, you will have problems with memory
 *                        management.
 * @param[in]      nChars is the upper limit of TextBlob string.
 * @param[in]      str    is null-terminated and/or at least @a nChars long.
 * @see            textBlobDelete().
 *
 * @return @a tbPtr if construction was successful. Otherwise, NULL.
 *
 * @note If @a tbPtr is NULL, then NULL will simply be returned.
 */
TextBlob* textBlobCtor_n(TextBlob* const tbPtr, size_t const nChars, char const str[nChars]);

/**
 * Deletes the TextBlob specified by @a tbPtr.
 *
 * @param[in] tbPtr is the pointer to the TextBlob object.
 *
 * @note If @a tbPtr is NULL, then nothing happens.
 *
 * @warning @a tbPtr must be initialised either by using textBlobNew() or textBlobNew_n(), or using
 *          malloc(), followed by textBlobCtor() or textBlobCtor_n(). If neither of these
 *          init sequences have been taken, then expect U.B. from this function. You may even
 *          very likely crash the program!
 */
void textBlobDelete(TextBlob* const tbPtr);

/**
 * Splits TextBlob specified by @a tbSrc at index @a n.
 *
 * @a tbSrc will become the left-half of the original blob, while the right half will be allocated
 * a new TextBlob object and linked after @a tbSrc.
 *
 * @param[in,out] tbSrc must be properly initialised.
 * @param[in]     n     must be a non-zero integer that does not exceed the bounds of @a tbSrc.
 *
 * @warning Program will crash if value of @a n does not make any sense. E.g. @a n is set to
 *          the null byte of the string of @a tbSrc.
 *
 * @return @a tbSrc if split was successful. NULL if at any point memory allocation fails, or if
 *         @a tbSrc is NULL.
 */
TextBlob* textBlobSplit(TextBlob* const tbSrc, size_t const n);

/*------------------*
 * Helper Functions *
 *------------------*/
char const* textBlobGetStr(const TextBlob* const tbPtr);
size_t textBlobGetLen(const TextBlob* const tbPtr);
TextBlob* textBlobGetPrev(const TextBlob* const tbPtr);
TextBlob* textBlobGetNext(const TextBlob* const tbPtr);

TextBlob* textBlobReplace(TextBlob* const tbPtr, char const newStr[static 1]);
TextBlob* textBlobReplace_n(TextBlob* const tbPtr, size_t const nChars, char const newStr[nChars]);

#endif /* TEXTBLOB_H_ */

