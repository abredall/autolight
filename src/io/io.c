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
#include <stdio.h> // file io
#include <stdlib.h> // EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // sterror()
#include <linux/limits.h>

int read_str(char * file_name, char var[PATH_MAX]) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	if (fscanf(fp_in, "%1023[^\n]%*c", var) != 1) {
		fprintf(stderr, "ERROR: Could not read string from %s. Make sure file is formatted properly.\n", file_name);
		return EXIT_FAILURE;
	}

	fclose(fp_in);

	return EXIT_SUCCESS;
}

int write_int(char * file_name, int input) {
	FILE * fp_out = fopen(file_name, "w");

	if (fp_out == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(fp_out, "%d", input);
	fclose(fp_out);

	return EXIT_SUCCESS;
}

int read_int(char * file_name, int * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	int output;
	if (fscanf(fp_in, "%d", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read int from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);
	*var = output;

	return EXIT_SUCCESS;
}

int read_long(char * file_name, unsigned long int * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	unsigned long int output;
	if (fscanf(fp_in, "%li", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read long from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);

	*var = output;

	return EXIT_SUCCESS;
}

int read_float(char * file_name, float * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	float output;
	if (fscanf(fp_in, "%f", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read float from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);

	*var = output;

	return EXIT_SUCCESS;
}
