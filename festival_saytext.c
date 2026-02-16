
#include <stdio.h>

#include <string.h>

#include "festival_saytext.h"

int festival_saytext(char *msg) {

  char cmd_str[256];

  int retval;

  FILE *fp;
  
  memset(cmd_str, 0, sizeof(cmd_str));

  fp = popen("/usr/bin/festival --pipe", "w");
  if (fp == NULL) {
    perror("popen");
    return -1;
  }

  retval = fprintf(fp, "(SayText \"%s\")\n", msg);
  if (retval < 0) {
    fprintf(stderr, "%s: Trouble outputting command to festival speech engine.\n", __FUNCTION__);
  }
  
  retval = pclose(fp);
  if (retval == -1) {
    perror("pclose");
    return -1;
  }
  
  return 0;
  
}
