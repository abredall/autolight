/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../config.h"

extern int test_read_screen_bri();
extern int test_write_screen_bri();
extern int test_read_screen_max_bri();

int test_screen() {
	printf("Testing connection to screen...\n");

	int result;
	int n_passed = 0;
	int n_failed = 0;

	result = test_read_screen_bri();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	result = test_write_screen_bri();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	result = test_read_screen_max_bri();
	if (result == EXIT_SUCCESS) {
		n_passed += 1;
	} else if (result == EXIT_FAILURE) {
		n_failed += 1;
	}

	printf("Passed: %d\t Failed: %d\n", n_passed, n_failed);
	return 0;
}

int test_read_screen_bri() {
	printf("Test: Read screen brightness... ");
	FILE * fp_in = fopen(cfg.files.bri, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_write_screen_bri() {
	printf("Test: Write screen brightness... ");
	FILE * fp_out = fopen(cfg.files.bri, "w");

	if (fp_out == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_out);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_read_screen_max_bri() {
	printf("Test: Read screen max brightness... ");
	FILE * fp_in = fopen(cfg.files.max_bri, "r");

	if (fp_in == NULL) {
		printf("Failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}
