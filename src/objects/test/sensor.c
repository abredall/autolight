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

	FILE * fp_in = fopen(cfg.files.als_lux, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.als_lux, strerror(errno));
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

	FILE * fp_in = fopen(cfg.files.als_freq, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.als_freq, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

void print_als_not_connected() {
	printf("Failed\n  ->Could not connect to ALS.\n");
	fflush(stdout);
}
