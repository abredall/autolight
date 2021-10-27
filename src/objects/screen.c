/*
 *   Copyright 2021 John W. Bredall
 *
 *   This file is part of autolight.
 *
 *   autolight is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   autolight is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with autolight.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include <stdbool.h> // bool
#include <stdio.h> //printf
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "../io.h" // read_from(), write_to()
#include "../cfg.h" // cfg
#include "screen.h" // screen

extern void screen_initialize();
extern void screen_connect();
extern void screen_init_paths();
extern int screen_get_bri();
extern int screen_set_bri();
extern int screen_get_max_bri();

void screen_initialize() {
	screen_connect();

	if (screen.online) {
		screen.bri.min = 1;
		screen_get_max_bri();
		screen_get_bri();
		screen.bri.ch = false;
	} else {
		fprintf(stderr, "WARNING: Could not connect to screen %s. Disabling functionality.\n", screen.name);
		fflush(stdout);
	}
}

void screen_connect() {
	strcpy(screen.name, cfg.devs.screen);

	if (screen.name[0] == '\0') {
		screen.online = 0;
		return;
	}
	join_paths(screen.dir, 2, DEF_SCREEN_DIR, screen.name);

	DIR * dir = opendir(screen.dir);

	if (dir) {
		closedir(dir);
		screen.online = 1;
		screen_init_paths();
	} else if (ENOENT == errno) {
		screen.online = 0;
	} else {
		// opendir() failed for some other reason.
		fprintf(stderr, "ERROR: Could not connect to screen %s: %s\n", screen.name, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void screen_init_paths() {
	join_paths(screen.files.bri, 2, screen.dir, DEF_SCREEN_BRI_FNAME);
	join_paths(screen.files.max_bri, 2, screen.dir, DEF_SCREEN_MAX_BRI_FNAME);
}


int screen_get_bri() {
	int result = read_int(screen.files.bri, &screen.bri.curr);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get screen brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int screen_set_bri() {
	int result = write_int(screen.files.bri, screen.bri.curr);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not set screen brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int screen_get_max_bri() {
	int result = read_int(screen.files.max_bri, &screen.bri.max);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get maximum brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

