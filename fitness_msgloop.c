
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>

#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>

#include <yaml.h>

#include "festival_saytext.h"

#include "difftime.h"

#include "fitness_msgloop.h"

int fitness_msgloop(long int num_hours, long int num_pushups) {

  struct timespec ts_interval;

  uint64_t ns_total;

  double jitter_s, pre_s;

  int retval;
  
  jitter_s = 3.0;

  pre_s = 3.0;
    
  {

    long int pushup_idx;

    struct timespec start, now;

    clock_gettime(CLOCK_REALTIME, &start);
    
    pushup_idx = 0;
    
    do {

      struct timespec elapsed_ts;

      pushup_idx++;
      
      clock_gettime(CLOCK_REALTIME, &now);

      elapsed_ts = subtract_ts(&start, &now);
      
      printf("[%ld.%09lds] Pushup #%ld\n", elapsed_ts.tv_sec, elapsed_ts.tv_nsec, pushup_idx);

      {
      
	char *msg;

	msg = "Perform a good form pushup.";

	retval = festival_saytext(msg);
	if (retval == -1) {
	  fprintf(stderr, "%s: Error with festival speech text.\n", __FUNCTION__);
	  return -1;
	}
	
      }

      ns_total = ((1.0e9 * 3600 * num_hours) / num_pushups) - (0.5 * jitter_s) + (drand48() * jitter_s) - pre_s;

      ts_interval.tv_sec = (ns_total / 1000000000);
      ts_interval.tv_nsec = (ns_total % 1000000000);
      
      retval = clock_nanosleep(CLOCK_REALTIME, 0, &ts_interval, NULL);
      if (retval == 0) {
	continue;
      }
      
      else {

	printf("clock_nanosleep was interrupted.\n");

	printf("retval %d\n", retval);
	
      }

    } while (pushup_idx < num_pushups);

  }
  
  printf("OK\n");
  
  return 0;

}
