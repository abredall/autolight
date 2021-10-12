/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../config.h"

extern int test_read_lux_value();
extern int test_read_als_freq();

int test_sensor() {
	printf("Testing connection to sensor...\n");

	int result;
	int n_passed = 0;
	int n_failed = 0;

	result = test_read_lux_value();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	result = test_read_als_freq();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	printf("Passed: %d\t Failed: %d\n", n_passed, n_failed);
	return 0;
}

int test_read_lux_value() {
	printf("Test: Read lux value... ");
	FILE * fp_in = fopen(cfg.files.als_lux, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_read_als_freq() {
	printf("Test: Read ALS frequency... ");
	FILE * fp_in = fopen(cfg.files.als_freq, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}
