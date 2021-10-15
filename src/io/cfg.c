#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../cfg.h"

char * read_cfg_str(char *desired_name) {
	char name[PATH_MAX];
	char val[PATH_MAX];

	FILE * cfg_in = fopen(cfg.fname, "r");
	if (cfg_in == NULL) {
		fprintf(stderr, "ERROR: Could not read config file %s: %s\n", cfg.fname, strerror(errno));
		exit(EXIT_FAILURE);
	}

	while (fscanf(cfg_in, "%1023[^=]=%1023[^\n]%*c", name, val) == 2) {
		if (0 == strcmp(name, desired_name)) {
			return strdup(val);
		}
	}

	return NULL;
}

int read_cfg_long(char * desired_name, unsigned long int * ret) {
    char * temp = read_cfg_str(desired_name);
	if (temp == NULL) return 1;

    char * stop;
    *ret = strtol(temp, &stop, 10);
	int ret_val = stop == NULL || *stop != '\0';
    free(temp);
    return ret_val;
}

int read_cfg_float(char * desired_name, float * ret) {
    char * temp = read_cfg_str(desired_name);
	if (temp == NULL) return 1;

    char * stop;
    *ret = strtof(temp, &stop);
	int ret_val = stop == NULL || *stop != '\0';
    free(temp);
    return ret_val;
}
