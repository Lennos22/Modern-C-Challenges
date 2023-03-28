/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/14:43
 */
#include "blob.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/* Private function prototypes */
blob blob_get(char text[static 1]);

blob* blob_init(blob* bp, char text[static 1]) {
	if (bp) *bp = blob_get(text);

	return bp;
}

blob* blob_split(blob* bp, size_t n) {
assert(n);
assert(n < strlen(bp->text)+1);
	if (bp) {
		blob next_blob = {0};
		blob_init(&next_blob, bp->text+n);
		next_blob.prev = bp;
		next_blob.next = bp->next;

		char new_str[n+1];
		strncpy(new_str, bp->text, n);
		new_str[n] = 0;

		bp->text = new_str;
		bp->next = &next_blob;
	}

	return bp;
}

 void blob_print(blob* bp) {
	 /* Iterate to the left of blob until HEAD is reached */
	 while (bp->prev)
		 bp = bp->prev;
	 /* Print connected blobs until TAIL is reached */
	 while (bp) {
		 printf("%s", bp->text);
		 bp = bp->next;
	 }
 }

/* Private functions */
blob blob_get(char text[static 1]) {
	blob ret = {
		.text = text,
		.prev = (void*)0,
		.next = (void*)0,
	};
	return ret;
}
