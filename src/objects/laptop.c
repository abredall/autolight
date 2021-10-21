#include <stdio.h> // fopen()
#include <stdlib.h> //EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // strstr()
#include "../cfg.h" // cfg
#include "../io.h" // read_from()
#include "laptop.h" // laptop

int check_lid_state() {
	char lid_state[PATH_MAX];
	int result = read_str(cfg.files.lid_state, lid_state);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get lid state.\n");
		exit(EXIT_FAILURE);
	}

	if (strstr(lid_state, "open") != NULL) {
		laptop.lid_state = 1;
	} else if (strstr(lid_state, "closed") != NULL) {
		laptop.lid_state = 0;
	}
	return 0;
}
int check_plug_state() {
	int result = read_int(cfg.files.plug_state, &laptop.plug_state);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get plug state.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

void laptop_check_states() {
	if (laptop.lid_online) {
		check_lid_state();
	}
	if (laptop.plug_online) {
		check_plug_state();
	}
}

void laptop_initialize() {
	laptop_check_states();
}
