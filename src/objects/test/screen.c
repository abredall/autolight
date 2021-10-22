/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../cfg.h"
#include "../../objects.h"

extern int test_read_screen_bri();
extern int test_write_screen_bri();
extern int test_read_screen_max_bri();

int test_screen(int * n_pass, int * n_fail) {
	printf("Testing connection to screen...\n");
	fflush(stdout);

	screen_connect();

	int result;

	result = test_read_screen_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_write_screen_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_read_screen_max_bri();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	printf("Screen tests complete!\n\n");
	fflush(stdout);
	return 0;
}

void print_screen_not_connected();

int test_read_screen_bri() {
	printf("Test: Read screen brightness... ");
	fflush(stdout);

	if (!screen.online) {
		print_screen_not_connected();
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(screen.files.bri, "r");

	if (fp_in == NULL) {
		printf("Failed\n  -> Could not read %s: %s\n", screen.files.bri, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

int test_write_screen_bri() {
	printf("Test: Write screen brightness... ");
	fflush(stdout);

	if (!screen.online) {
		print_screen_not_connected();
		return EXIT_FAILURE;
	}

	FILE * fp_out = fopen(screen.files.bri, "w");

	if (fp_out == NULL) {
		printf("Failed\n  -> Could not write to %s: %s\n", screen.files.bri, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_out);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

int test_read_screen_max_bri() {
	printf("Test: Read screen max brightness... ");
	fflush(stdout);

	if (!screen.online) {
		print_screen_not_connected();
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(screen.files.max_bri, "r");

	if (fp_in == NULL) {
		printf("Failed\n  -> Could not read %s: %s\n", screen.files.max_bri, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

void print_screen_not_connected() {
	printf("Failed\n  -> Could not connect to screen %s.\n", screen.name);
	fflush(stdout);
}
