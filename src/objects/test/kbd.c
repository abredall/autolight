/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../cfg.h"

extern int test_read_kbd_bri();
extern int test_write_kbd_bri();
extern int test_read_kbd_max_bri();

int test_kbd(int * n_pass, int * n_fail) {
	printf("Testing connection to keyboard...\n");

	int result;

	result = test_read_kbd_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_write_kbd_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_read_kbd_max_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	return 0;
}

int test_read_kbd_bri() {
	printf("Test: Read keyboard brightness... ");
	FILE * fp_in = fopen(cfg.files.kbd_bri, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.kbd_bri, strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_write_kbd_bri() {
	printf("Test: Write keyboard brightness... ");
	FILE * fp_out = fopen(cfg.files.kbd_bri, "w");

	if (fp_out == NULL) {
		printf("Failed\n - Could not write to %s: %s\n", cfg.files.kbd_bri, strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_out);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}

int test_read_kbd_max_bri() {
	printf("Test: Read keyboard max brightness... ");
	FILE * fp_in = fopen(cfg.files.kbd_max_bri, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.kbd_max_bri, strerror(errno));
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	return EXIT_SUCCESS;
}
