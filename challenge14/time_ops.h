/* Created by Nelson Cardona
 * Creation Date/Time: 31-03-23/23:14
 */
#ifndef TIME_OPS_H
#define TIME_OPS_H

#include <time.h>

/**
  * Returns the ABSOLUTE difference between two timespec values.
  * @note Adapted from Exs 43.
  * @param[in] ts1,ts2 The timespec objects.
  * @return A timespec struc containing the difference between @a ts1 and @a ts2.
  */
struct timespec timespec_diff(struct timespec ts1, struct timespec ts2);

/**
  * Prints @a ts in seconds.nanoseconds format.
  * @param[in] ts timespec object that will be printed.
  */
void timespec_print(struct timespec ts);

#endif
