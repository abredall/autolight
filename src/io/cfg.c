#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

char * read_cfg_str(char * cfg_name, char *desired_name) {
	char name[BUFF_SIZE];
	char val[BUFF_SIZE];

	FILE * cfg_in = fopen(cfg_name, "r");
	if (cfg_in == NULL) {
		return NULL;
	}

	while (fscanf(cfg_in, "%1023[^=]=%1023[^\n]%*c", name, val) == 2) {
		if (0 == strcmp(name, desired_name)) {
			return strdup(val);
		}
	}

	return NULL;
}

int read_cfg_long(char * cfg_name, char * desired_name, unsigned long int * ret) {
    char * temp = read_cfg_str(cfg_name, desired_name);
	if (temp == NULL) return 1;

    char * stop;
    *ret = strtol(temp, &stop, 10);
	int ret_val = stop == NULL || *stop != '\0';
    free(temp);
    return ret_val;
}

int read_cfg_float(char * cfg_name, char * desired_name, float * ret) {
    char * temp = read_cfg_str(cfg_name, desired_name);
	if (temp == NULL) return 1;

    char * stop;
    *ret = strtof(temp, &stop);
	int ret_val = stop == NULL || *stop != '\0';
    free(temp);
    return ret_val;
}
