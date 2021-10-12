/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../config.h"

int test_read_lid_state() {
	printf("Test: Read lid state... ");
	FILE * fp_in = fopen(cfg.files.lid_state, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_read_plug_state() {
	printf("Test: Read plug state... ");
	FILE * fp_in = fopen(cfg.files.plug_state, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_laptop() {
	printf("Testing knowledge of laptop state...\n");

	int result;
	int n_passed = 0;
	int n_failed = 0;


	result = test_read_lid_state();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	result = test_read_plug_state();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	printf("Passed: %d\t Failed: %d\n", n_passed, n_failed);
	return 0;
}

