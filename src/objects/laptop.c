#include <stdio.h> // fopen()
#include <stdlib.h> //EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // strstr()
#include "../config.h" // cfg
#include "../io.h" // read_from()
#include "laptop.h" // laptop

int check_lid_state() {
	char lid_state[20];

	FILE * fp_lid = fopen(cfg.files.lid_state, "r");
	if (fp_lid == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", cfg.files.lid_state, strerror(errno));
		fprintf(stderr, "ERROR: Could not get lid state.\n");
		exit(EXIT_FAILURE);
	}
	fgets(lid_state, 19, fp_lid);
	fclose(fp_lid);

	if (strstr(lid_state, "open") != NULL) {
		laptop.lid_state = 1;
	} else if (strstr(lid_state, "closed") != NULL) {
		laptop.lid_state = 0;
	}

	return 0;
}
int check_plug_state() {
	int result = read_from(cfg.files.plug_state, &laptop.plug_state);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get plug state.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

void laptop_check_states() {
	check_lid_state();
	check_plug_state();
}

void laptop_initialize() {
	laptop_check_states();
}
