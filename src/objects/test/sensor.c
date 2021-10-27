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
/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../cfg.h"
#include "../../objects.h"

extern int test_read_lux_value();
extern int test_read_als_freq();

int test_sensor(int * n_pass, int * n_fail) {
	printf("Testing connection to sensor...\n");
	fflush(stdout);

	sensor_connect();

	int result;

	result = test_read_lux_value();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_read_als_freq();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	printf("Sensor tests complete!\n\n");
	fflush(stdout);
	return 0;
}

void print_als_not_connected();

int test_read_lux_value() {
	printf("Test: Read lux value... ");
	fflush(stdout);

	if (!sensor.online) {
		print_als_not_connected();
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(sensor.files.input, "r");

	if (fp_in == NULL) {
		printf("Failed\n  -> Could not read %s: %s\n", sensor.files.input, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

int test_read_als_freq() {
	printf("Test: Read ALS frequency... ");
	fflush(stdout);

	if (!sensor.online) {
		print_als_not_connected();
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(sensor.files.freq, "r");

	if (fp_in == NULL) {
		printf("Failed\n  -> Could not read %s: %s\n", sensor.files.freq, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

void print_als_not_connected() {
	printf("Failed\n  -> Could not connect to ALS %s\n", sensor.name);
	fflush(stdout);
}
