
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

#include "rndseed_setup.h"

int rndseed_setup(char *rnd_fn) {

  int rnd_fd;

  long seedval;

  ssize_t bytes_read;

  int retval;
    
  rnd_fd = open(rnd_fn, O_RDONLY);
  if (rnd_fd == -1) {
    perror("open");
    return -1;
  }
    
  bytes_read = read(rnd_fd, &seedval, sizeof(seedval));
  if (bytes_read != sizeof(seedval)) {
    perror("read");
    return -1;
  }
    
  srand48(seedval);

  retval = close(rnd_fd);
  if (retval == -1) {
    perror("close");
    return -1;
  }

  return 0;
  
}

