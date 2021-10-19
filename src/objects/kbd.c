#include <stdbool.h> // bool
#include <stdio.h> //printf
#include <stdlib.h>
#include "../io.h" // read_from(), write_to()
#include "../cfg.h" // cfg
#include "kbd.h" // screen

int kbd_check_bri() {
	int result = read_int(cfg.files.kbd_bri, &kbd.curr_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int kbd_set_bri() {
	int result = write_int(cfg.files.kbd_bri, kbd.curr_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not set keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int kbd_get_max_bri() {
	int result = read_int(cfg.files.kbd_max_bri, &kbd.max_bri);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get maximum keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

void kbd_initialize() {
	kbd.min_bri = 0;
	kbd_get_max_bri();
	kbd_check_bri();
	kbd.ch_bri = false;
}

