#include <stdbool.h> // bool
#include <stdio.h> //printf
#include <stdlib.h>
#include "../io.h" // read_from(), write_to()
#include "../config.h" // cfg
#include "screen.h" // screen

int screen_check_bri() {
	int result = read_from(cfg.files.bri, &screen.curr_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get screen brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int screen_set_bri() {
	int result = write_to(cfg.files.bri, screen.curr_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not set screen brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int screen_get_max_bri() {
	int result = read_from(cfg.files.max_bri, &screen.max_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get maximum brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

void screen_initialize() {
	screen.min_bri = 1;
	screen_get_max_bri();
	screen_check_bri();
	screen.ch_bri = false;
}

