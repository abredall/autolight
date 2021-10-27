/*
 *   autolight: a lightweight ambient light sensor daemon
 *   Copyright (C) 2021 John W. Bredall
 *
 *   This file is part of autolight.
 *
 *   autolight is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   autolight is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with autolight.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../cfg.h"

void read_cfg_str(char * desired_name, char * ret, char * DEF_VALUE) {
	char name[PATH_MAX];
	char val[PATH_MAX];

	FILE * cfg_in = fopen(cfg.fname, "r");
	if (cfg_in == NULL) {
		fprintf(stderr, "ERROR: Could not read config file %s: %s\n", cfg.fname, strerror(errno));
		exit(EXIT_FAILURE);
	}

	while (fscanf(cfg_in, "%1023[^=]=%1023[^\n]%*c", name, val) == 2) {
		if (0 == strcmp(name, desired_name)) {
			strcpy(ret, val);
			return;
		}
	}

	strcpy(ret, DEF_VALUE);
}

int read_cfg_long(char * desired_name, unsigned long int * ret, unsigned long int DEF_VALUE) {
    char temp[PATH_MAX];
	read_cfg_str(desired_name, temp, '\0');
	if (temp == NULL) {
		*ret = DEF_VALUE;
		return 0;
	}

    char * stop;
    *ret = strtol(temp, &stop, 10);
	int ret_val = stop == NULL || *stop != '\0';
    return ret_val;
}

int read_cfg_float(char * desired_name, float * ret, float DEF_VALUE) {
    char temp[PATH_MAX];
	read_cfg_str(desired_name, temp, NULL);
	if (temp == NULL) {
		*ret = DEF_VALUE;
		return 0;
	}

    char * stop;
    *ret = strtof(temp, &stop);
	int ret_val = stop == NULL || *stop != '\0';
    return ret_val;
}
