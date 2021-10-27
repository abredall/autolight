/*
 *   autolight: a lightweight ambient light sensor daemon
 *   Copyright (C) 2021 John W. Bredall
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
#include "kbd.h" // kbd

extern void kbd_initialize();
extern void kbd_connect();
extern void kbd_init_paths();
extern int kbd_get_bri();
extern int kbd_set_bri();
extern int kbd_get_max_bri();

void kbd_initialize() {
	kbd_connect();

	if (kbd.online) {
		kbd.bri.min = 0;
		kbd_get_max_bri();
		kbd_get_bri();
		kbd.bri.ch = false;
	} else {
		fprintf(stderr, "WARNING: Could not connect to keyboard %s. Disabling functionality.\n", kbd.name);
		fflush(stdout);
	}
}

void kbd_connect() {
	strcpy(kbd.name, cfg.devs.kbd);

	if (kbd.name[0] == '\0') {
		kbd.online = 0;
		return;
	}

	join_paths(kbd.dir, 2, DEF_KBD_DIR, kbd.name);

	DIR * dir = opendir(kbd.dir);

	if (dir) {
		closedir(dir);
		kbd.online = 1;
		kbd_init_paths();
	} else if (ENOENT == errno) {
		kbd.online = 0;
	} else {
		// opendir() failed for some other reason.
		fprintf(stderr, "ERROR: Could not connect to keyboard %s: %s\n", kbd.name, strerror(errno));
		exit(EXIT_FAILURE);
	}

}

void kbd_init_paths() {
	join_paths(kbd.files.bri, 2, kbd.dir, DEF_KBD_BRI_FNAME);
	join_paths(kbd.files.max_bri, 2, kbd.dir, DEF_KBD_MAX_BRI_FNAME);
}

int kbd_get_bri() {
	int result = read_int(kbd.files.bri, &kbd.bri.curr);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int kbd_set_bri() {
	int result = write_int(kbd.files.bri, kbd.bri.curr);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not set keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int kbd_get_max_bri() {
	int result = read_int(kbd.files.max_bri, &kbd.bri.max);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get maximum keyboard brightness.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

