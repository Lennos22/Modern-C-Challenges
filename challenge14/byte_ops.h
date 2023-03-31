/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/17:22
 */
/** @file byte_ops.h */
#ifndef BYTE_OPS_H
#define BYTE_OPS_H

#include <stddef.h>

void byte_swp(void* p1, void* p2, size_t n);
void byte_cpy(void* dest, void const* src, size_t n);

#endif
