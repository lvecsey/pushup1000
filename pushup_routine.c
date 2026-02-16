
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

#include "rndseed_setup.h"

#include "yaml_msgloop.h"

#include "fitness_msgloop.h"

int main(int argc, char *argv[]) {

  char *yaml_fn;

  FILE *yaml_fp;
  
  char *yaml_str;

  int retval;
  
  {
  
    yaml_fn = argc>1 ? argv[1] : NULL;

    yaml_str = argc>2 ? argv[2] : NULL;
    
  }

  {

    yaml_fp = NULL;
    
  }
    
  if (yaml_fn != NULL) {

    yaml_fp = fopen(yaml_fn, "r");
    if (yaml_fp == NULL) {
      perror("fopen");
      return -1;
    }

  }

  if ((yaml_str != NULL) || (yaml_fp != NULL)) {
  
    {
      char *rnd_fn;
      rnd_fn = "/dev/urandom";
      retval = rndseed_setup(rnd_fn);
      if (retval == -1) {
	printf("%s: Problem with calling rndseed_setup.\n", __FUNCTION__);
	return -1;
      }
    }
  
    retval = yaml_msgloop(yaml_str, yaml_fp);
    if (retval == -1) {
      fprintf(stderr, "%s: Problem with call to yaml_msgloop.\n", __FUNCTION__);
      return -1;
    }

    return 0;
    
  }

  printf("Not configured; will not run.\n");
  
  return -1;

}
