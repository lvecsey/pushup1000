
#include <stdio.h>

#include <stdint.h>

#include <errno.h>

#include <yaml.h>

#include "fitness_msgloop.h"

#include "yaml_msgloop.h"

#define sample_yamlstr "hours: 10\npushups: 60\n\njitter_s: 3.0\npre_s: 3.0\n"

#define HAVE_HOURS 0x1
#define HAVE_PUSHUPS 0x2
#define CONFIGURED 0x4

int yaml_msgloop(char *yaml_str, FILE *yaml_fp) {

  yaml_parser_t parser;

  yaml_document_t document;
  
  long int num_hours;

  long int num_pushups;
  
  int retval;

  uint64_t state;
  
  printf("YAML: %s\n", yaml_get_version_string());

  {
  
    state = 0L;

    num_hours = 0;

    num_pushups = 0;

  }
    
  retval = yaml_parser_initialize(&parser);

  if (yaml_str != NULL) {
  
    yaml_parser_set_input_string(&parser, (const unsigned char*) yaml_str, strlen(yaml_str));

  }

  else if (yaml_fp != NULL) {
    
    yaml_parser_set_input_file(&parser, yaml_fp);
    
  }

  retval = yaml_parser_load(&parser, &document);
  if (retval != 1) {
    fprintf(stderr, "%s: Problem with parsing yaml contents into document.\n", __FUNCTION__);
    return -1;
  }
  
  {
  
    yaml_node_t *node = yaml_document_get_root_node(&document);
    
    for (yaml_node_pair_t *pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {

      yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);

      if (key_node->type == YAML_SCALAR_NODE) {

	yaml_node_t *value_node;
	
	char *key;

	char *value;
	
	key = (char*) key_node->data.scalar.value;

	value_node = yaml_document_get_node(&document, pair->value);

	if (!strncmp(key, "hours", 5)) {

	  value = (char*) value_node->data.scalar.value;

	  errno = 0;
	  num_hours = strtol(value, NULL, 10);
	  if (errno == EINVAL) {
	    return -1;
	  }

	  state |= HAVE_HOURS;
	  
	}

	if (!strncmp(key, "pushups", 7)) {

	  value = (char*) value_node->data.scalar.value;
	  
	  errno = 0;
	  num_pushups = strtol(value, NULL, 10);
	  if (errno == EINVAL) {
	    return -1;
	  }

	  state |= HAVE_PUSHUPS;
	  
	}
	
      }
	
    }

  }

  yaml_document_delete(&document);
  
  if ((state & HAVE_HOURS) && (state & HAVE_PUSHUPS)) {
    state |= CONFIGURED;
  }
  
  if (state & CONFIGURED) {

    if (num_hours <= 0 || num_pushups <= 0) {
      printf("Bad configuration.\n");
      return -1;
    }

    printf("YAML nodes specified configuration %ld %ld\n", num_hours, num_pushups);
    
    return fitness_msgloop(num_hours, num_pushups);

  }

  return 0;
  
}
