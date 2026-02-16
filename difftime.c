
#include <time.h>

#include "difftime.h"

struct timespec subtract_ts(struct timespec *a, struct timespec *b) {

  struct timespec res;

  int overflow;

  overflow = ((b->tv_nsec - a->tv_nsec) < 0);

  if (overflow) {

    res.tv_sec = 1 + (b->tv_sec - a->tv_sec);

    res.tv_nsec = 1000000000L + (b->tv_nsec - a->tv_nsec);
    
  }

  else {

    res.tv_sec = (b->tv_sec - a->tv_sec);

    res.tv_nsec = (b->tv_nsec - a->tv_nsec);
    
  }
  
  return res;

}
