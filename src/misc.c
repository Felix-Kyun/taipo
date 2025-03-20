#include "misc.h"
#include <time.h>

double get_seconds(void) {

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  return (ts.tv_sec) + (ts.tv_nsec / 1000000000.0);
}
