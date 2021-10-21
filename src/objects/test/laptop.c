/* Test laptop functionality */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../cfg.h"
#include "../../objects.h"

extern int test_read_lid_state();
extern int test_read_plug_state();

int test_laptop(int * n_pass, int * n_fail) {
	printf("Testing knowledge of laptop state...\n");
	fflush(stdout);

	int result;

	result = test_read_lid_state();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	result = test_read_plug_state();
	if (result == EXIT_SUCCESS) {
		*n_pass += 1;
	} else if (result == EXIT_FAILURE) {
		*n_fail += 1;
	}

	return 0;
}

int test_read_lid_state() {
	printf("Test: Read lid state... ");
	fflush(stdout);

	if (!laptop.lid_online) {
		printf("Failed\n - Could not connect to lid.\n");
		fflush(stdout);
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(cfg.files.lid_state, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.lid_state, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}

int test_read_plug_state() {
	printf("Test: Read plug state... ");
	fflush(stdout);

	if (!laptop.lid_online) {
		printf("Failed\n - Could not connect to plug.\n");
		fflush(stdout);
		return EXIT_FAILURE;
	}

	FILE * fp_in = fopen(cfg.files.plug_state, "r");

	if (fp_in == NULL) {
		printf("Failed\n - Could not read %s: %s\n", cfg.files.plug_state, strerror(errno));
		fflush(stdout);
		return EXIT_FAILURE;
	}

	fclose(fp_in);
	printf("Passed!\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}
