/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/23:12
 */
#include "time_ops.h"

#include <stdlib.h>
#include <stdio.h>

#define NSECS_PER_SEC 1E+9;

/* Returns the ABSOLUTE difference between two timespec values.
 * Adapted from Exs 43.
 */
struct timespec timespec_diff(struct timespec ts1, struct timespec ts2) {
	struct timespec result = {
		.tv_nsec = labs(ts1.tv_nsec - ts2.tv_nsec)
	};

#ifndef NDEBUG
printf("Initialised result: %zu.%09ld\n", result.tv_sec, result.tv_nsec);
#endif

	if (ts1.tv_sec < ts2.tv_sec) {
#ifndef NDEBUG
printf("ts1.tv_sec < ts2.tv_sec\n");
#endif
		result.tv_sec = ts2.tv_sec - ts1.tv_sec;
		if (ts2.tv_nsec < ts1.tv_nsec) {
			--result.tv_sec;
			result.tv_nsec = NSECS_PER_SEC - result.tv_nsec;
		}
	} else if (ts2.tv_sec < ts1.tv_sec) {
#ifndef NDEBUG
printf("ts2.tv_sec < ts1.tv_sec\n");
#endif
		result.tv_sec = ts1.tv_sec - ts2.tv_sec;
		if (ts1.tv_nsec < ts2.tv_nsec) {
			--result.tv_sec;
			result.tv_nsec = NSECS_PER_SEC - result.tv_nsec;
		}
	}
	
	return result;
}

void print_timespec(struct timespec ts) {
	printf("%zu.%09lds", ts.tv_sec, ts.tv_nsec);
}
