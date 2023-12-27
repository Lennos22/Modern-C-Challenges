/**
 * @file textblob.h
 *
 * Contains API for the TextBlob type.
 *
 * Created by Nelson Cardona
 * Creation Date/Time: 23-12-23/17:00
 */
#ifndef TEXTBLOB_H_
#define TEXTBLOB_H_
/**
 * @defgroup TextBlobAPI
 *
 * Store text in a doubly-linked list of "blobs".
 *
 * There will be a User Manual, at some point...
 *
 * @note There are multiple mentions of "full" or "proper" initialisation of a TextBlob object.
 *       The warning in the TextBlobDestruction module will clarify what full initialisation means.
 * @{
 */

/*-------------------*
 * C StdLib Includes *
 *-------------------*/
#include <stddef.h>
#include <stdbool.h>

/*-----------------*
 * Public Typedefs *
 *-----------------*/
typedef struct TextBlob TextBlob;

/**************************************************************************************************
 *                                      Public Functions                                          *
 **************************************************************************************************/

/**
 * @defgroup TextBlobGeneration
 *
 * Functions that create and/or init. new TextBlob objects.
 *
 * @warning Passing a NULL @a str will trigger an assertion and crash the program.
 * @{
 */
/**
 * @name TextBlob Generators
 *
 * Creates a new TextBlob of the given string, @a str.
 */
/** @{*/
/**
 * @param[in] str must be null-terminated.
 * 
 * @warning Passing a malformed string (e.g. not null-terminated) is U.B.
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
 * @param[in] nChars is the upper limit of chars to be copied from @a newStr.
 * @param[in] str    is null-terminated and/or at least @a nChars long.
 *
 * @return Pointer to new TextBlob, otherwise NULL, if initialisation fails.
 */
TextBlob* textBlobNew_n(size_t const nChars, char const str[nChars]);
/** @}*/

/**
 * @name TextBlob Constructors
 *
 * Constructors for TextBlob types.
 *
 * @warning Passing a NULL @a tbPtr will trigger an assertion and crash the program.
 */
/** @{*/
/**
 * Constructs the TextBlob specified by @a tbPtr using a NULL-TERMINATED string, @a str.
 *
 * @param[in,out] tbPtr should be uninitialised. Otherwise, you will have problems with memory
 *                      management.
 * @param[in]     str   must be null-terminated.
 * @see           textBlobDelete().
 *
 * @warning Passing a malformed string (e.g. not null-terminated) results in U.B.
 *
 * @return @a tbPtr if construction was successful. Otherwise, NULL.
 */
TextBlob* textBlobCtor(TextBlob* const tbPtr, char const str[static 1]);

/**
 * Bounded - therefore, SAFER - version of textBlobCtor().
 *
 * It limits the number of characters in @a tbPtr to @a nChars. If @a str is null-terminated
 * before @a nChars, the true length will be reflected, accordingly. Therefore, do not expect @a
 * nChars to be the final length of %a tbPtr.
 *
 * @param[in,out] tbPtr  should be uninitialised. Otherwise, you will have problems with memory
 *                       management.
 * @param[in]     nChars is the upper limit of chars to be copied from @a newStr.
 * @param[in]     str    is null-terminated and/or at least @a nChars long.
 * @see           textBlobDelete().
 *
 * @return @a tbPtr if construction was successful. Otherwise, NULL.
 */
TextBlob* textBlobCtor_n(TextBlob* const tbPtr, size_t const nChars, char const str[nChars]);
/** @}*/
/**@}*/

/**
 * @defgroup TextBlobDestruction
 *
 * Functions that de-initialise and/or delete TextBlob objects.
 *
 * @warning @a tbIn must be initialised either by using textBlobNew() or textBlobNew_n(), or using
 *          malloc(), followed by textBlobCtor() or textBlobCtor_n(). If neither of these
 *          init sequences have been taken, then expect U.B. from this function. You may even
 *          very likely crash the program!
 *
 * @note If @a tbIn is NULL, then nothing happens.
 * @{
 */
/**
 * @name Deletion
 */
/** @{*/
/**
 * Deletes the TextBlob specified by @a tbIn.
 *
 * @param[in] tbIn is the pointer to the TextBlob object.
 */
void textBlobDelete(TextBlob* const tbIn);
/** @}*/

/**
 * @name Destructor
 */
/** @{*/
/**
 * Destructor for TextBlob objects.
 *
 * Not really necessary to include in API, since you may as well just use textBlobDelete(),
 * instead. But, it is included on the rare occassion it is ever needed.
 *
 * @param[in] tbIn must refer to a FULLY initialised TextBlob object. Otherwise, U.B. occurs. You
 *                  may even very likely crash the program!
 */
void textBlobDtor(TextBlob* const tbIn);
/** @}*/
/**@}*/

/**
 * @defgroup TextBlobNodeOperations
 *
 * Operations on TextBlob objects as nodes of a doubly-linked list.
 *
 * Generally, these operiations will return NULL or 0-equivalent value if the specified pointer to
 * TextBlob object is NULL.
 * @{
 */
/**
 * @name Blob Split Ops.
 *
 * Split operations on TextBlob objects.
 *
 * @a tbSrc will generally be the leftmost part of the text after splitting, and the rest will
 * be joined to it in their corresponding order.
 */
/** @{*/
/**
 * Splits TextBlob specified by @a tbSrc at index @a n.
 *
 * @a tbSrc will become the left part of the original blob, while the right part will be allocated
 * a new TextBlob object and linked after @a tbSrc.
 *
 * @param[in,out] tbSrc must be FULLY initialised.
 * @param[in]     n     must be a non-zero integer that does not exceed the bounds of @a tbSrc.
 *
 * @warning Program will crash if value of @a n does not make any sense. E.g. @a n is set to
 *          the null byte of the string of @a tbSrc (or further past text bounds).
 *
 * @return @a tbSrc if split was successful. NULL if at any point memory allocation fails.
 */
TextBlob* textBlobSplit(TextBlob* const tbSrc, size_t const n);

/**
 * Separates TextBlob object, @a tbSrc, by specified character separator, @a separator.
 *
 * Will find ALL locations of @a separator and separate from RIGHT side of blob. The separated
 * blobs will be joined together contiguously in the original order of @a tbSrc.
 *
 * @param[in,out] tbSrc     must be properly initialised.
 * @param[in]     separator is a single, 8-bit ASCII char.
 *
 * @return TRUE if separation was successful. FALSE if AT LEAST ONE separator fails to separate.
 *
 * @note Function will still attempt to separate as many times as possible even if FALSE is
 *       returned. Therefore, it will be up to the user to check and handle the error, accordingly.
 */
bool textBlobSeparateBy(TextBlob* const tbSrc, char const separator);
/** @}*/

/**
 * @name Blob Merge Ops.
 *
 * Merge operations on TextBlob objects.
 *
 * @a tbFront will be the front part of the (sub-)list of TextBlob objects, and will hold the
 * fully merged text after operation.
 */
/** @{*/
/**
 * Merges two consecutive TextBlob objects.
 *
 * If operation was successful, the tail blob will be deleted via textBlobDelete(). Otherwise,
 * It will be left as is, connected to @a tbFront.
 *
 * @warning Users should ALWAYS CHECK the result of the join operation. It will be their
 *          responsibility to handle the error as per their program's requirements.
 *
 * @param[in,out] tbFront is the head of the two blobs. It must be connected to the tail blob.
 *
 * @return @a tbFront if join is successful, otherwise NULL.
 *
 * @note Success also includes the case where @a tbFront is already the last element in the list.
 *       In this case, nothing happens.
 */
TextBlob* textBlobJoin(TextBlob* const tbFront);
/** @}*/
/**@}*/

/*------------------*
 * Helper Functions *
 *------------------*/
/**
 * @defgroup TextBlobGetters
 *
 * Getters for TextBlob types.
 *
 * Generally, if @a tbIn is NULL, then a 0-equivalent value will be returned.
 * @{
 */
/**
 * @name Getters
 *
 * Getters for TextBlob types.
 */
/** @{*/
/**
 * Retrieves string of text from TextBlob.
 *
 * @note Retrieved string is READ-ONLY, as U.B. would result if it is modified in any way.
 *
 * @param[in] tbIn is the pointer to TextBlob object.
 *
 * @return String from @a tbIn that is READ-ONLY.
 */
char const* textBlobGetStr(const TextBlob* const tbIn);

/**
 * Retrieves length of text from TextBlob.
 *
 * @param[in] tbIn is the pointer to TextBlob object.
 *
 * @return Length of text contained in TextBlob.
 */
size_t textBlobGetLen(const TextBlob* const tbIn);

/**
 * Retrieves pointer to previous TextBlob in linked list.
 *
 * @param[in] tbIn is the pointer to CURRENT textBlob object.
 *
 * @return Pointer to previous TextBlob in linked list.
 */
TextBlob* textBlobGetPrev(const TextBlob* const tbIn);

/**
 * Retrieves pointer to next TextBlob in linked list.
 *
 * @param[in] tbIn is the pointer to CURRENT TextBlob object.
 *
 * @return Pointer to next TextBlob in linked list.
 */
TextBlob* textBlobGetNext(const TextBlob* const tbIn);
/** @}*/
/**@}*/

/**
 * @defgroup TextBlobSetters
 *
 * Setters for TextBlob types.
 * 
 * @warning Passing a NULL @a str will trigger an assertion and crash the program.
 * @{
 */
/**
 * @name Replace Ops.
 *
 * Replaces text in TextBlob with specified string, @a newStr.
 */
/** @{*/
/**
 * @param[in,out] tbPtr  must be properly initialised.
 * @param[in]     newStr is replacment text for @a tbPtr.
 *
 * @return @a tbPtr if replacement was successful. NULL if unsuccessful, or if tbPtr is NULL.
 */
TextBlob* textBlobReplace(TextBlob* const tbPtr, char const newStr[static 1]);

/**
 * Bounded - therefore, SAFER - version of textBlobReplace().
 *
 * It limits the number of characters in @a tbPtr to @a nChars. If @a newStr is null-terminated
 * before @a nChars, the true length will be reflected, accordingly. Therefore, do not expect @a
 * nChars to be the final length of @a tbPtr.
 *
 * @param[in,out] tbPtr  must be properly initialised.
 * @param[in]     nChars is the upper limit of chars to be copied from @a newStr.
 * @param[in]     newStr is null-terminated and/or at least @a nChars long.
 * @see           textBlobReplace().
 * 
 * @return @a tbPtr if replacement was successful. NULL if unsuccessful, or if tbPtr is NULL.
 */
TextBlob* textBlobReplace_n(TextBlob* const tbPtr, size_t const nChars, char const newStr[nChars]);
/** @}*/

/**
 * @name Append Ops.
 *
 * Appends @a str to existing text from @a tbPtr.
 */
/** @{*/
/**
 * @param[in,out] tbPtr must be properly initialised.
 * @param[in]     str   is replacment text for @a tbPtr.
 *
 * @return @a tbPtr if @a str was succesfully appended. NULL if unsuccessful, or if tbPtr is NULL.
 */
TextBlob* textBlobAppend(TextBlob* const tbPtr, char const str[static 1]);

/**
 * Bounded - therefore, SAFER - version of textBlobAppend().
 *
 * It limits the number of characters in @a tbPtr to @a nChars. If @a str is null-terminated
 * before @a nChars, the true length will be reflected, accordingly. Therefore, do not expect @a
 * nChars to be the final length of @a tbPtr.
 *
 * @param[in,out] tbPtr  must be properly initialised.
 * @param[in]     nChars is the upper limit of chars to be copied from @a str.
 * @param[in]     str    is null-terminated and/or at least @a nChars long.
 * @see           textBlobAppend().
 * 
 * @return @a tbPtr if @a str was succesfully appended. NULL if unsuccessful, or if tbPtr is NULL.
 */
TextBlob* textBlobAppend_n(TextBlob* const tbPtr, size_t const nChars, char const str[nChars]);
/** @}*/
/**@}*/

/**@}*/
#endif /* TEXTBLOB_H_ */

