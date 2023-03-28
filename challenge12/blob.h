/* Created by Nelson Cardona
 * Creation Date/Time: 28-03-23/12:41
 */
#ifndef BLOB_H
#define BLOB_H
#include <stddef.h>

typedef struct blob blob;

struct blob {
	char* text;
	blob* prev;
	blob* next;
};

blob* blob_init(blob* bp, char text[static 1]);
blob* blob_split(blob* bp, size_t n);
void blob_print(blob* bp);

#endif
