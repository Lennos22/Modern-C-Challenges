/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/17:21
 */
#include "byte_ops.h"

#include <assert.h>

void byte_swp(void* p1, void* p2, size_t n) {
assert(p1);
assert(p2);
	unsigned char tmp[n];
	unsigned char* P1 = p1;
	unsigned char* P2 = p2;

	byte_cpy(tmp, P1, n);
	byte_cpy(P1, P2, n);
	byte_cpy(P2, tmp, n);
}

void byte_cpy(void* dest, void const* src, size_t n) {
assert(dest);
assert(src);
	unsigned char* Dest = dest;
	unsigned char const* Src = src;

	for (size_t i = 0; i < n; ++i)
		*(Dest+i) = *(Src+i);
}
