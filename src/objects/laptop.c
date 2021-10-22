#include <stdio.h> // fopen()
#include <stdlib.h> //EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // strstr()
#include <dirent.h>
#include <errno.h>
#include "../cfg.h" // cfg
#include "../io.h" // read_from()
#include "laptop.h" // laptop

extern void laptop_initialize();
extern void lid_initialize();
extern void lid_connect();
extern void lid_init_paths();
extern int check_lid_state();
extern void plug_initialize();
extern void plug_connect();
extern void plug_init_paths();
extern int check_plug_state();

void laptop_initialize() {
	lid_initialize();
	plug_initialize();
}

void lid_initialize() {
	lid_connect();

	if (laptop.lid.online) {
		check_lid_state();
	} else {
		fprintf(stderr, "WARNING: Could not connect to lid %s. Disabling functionality.\n", laptop.lid.name);
		fflush(stdout);
	}
}

void lid_connect() {
	strcpy(laptop.lid.name, cfg.devs.lid);

	if (laptop.lid.name[0] == '\0') {
		laptop.lid.online = 0;
		return;
	}
	join_paths(laptop.lid.dir, 2, DEF_LID_DIR, laptop.lid.name);

	DIR * dir = opendir(laptop.lid.dir);

	if (dir) {
		closedir(dir);
		laptop.lid.online = 1;
		lid_init_paths();
	} else if (ENOENT == errno) {
		laptop.lid.online = 0;
	} else {
		// opendir() failed for some other reason.
		fprintf(stderr, "ERROR: Could not connect to lid %s: %s\n", laptop.lid.name, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void lid_init_paths() {
	join_paths(laptop.lid.files.state, 2, laptop.lid.dir, DEF_LID_STATE_FNAME);
}

int check_lid_state() {
	char lid_state[PATH_MAX];
	int result = read_str(laptop.lid.files.state, lid_state);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get lid state.\n");
		exit(EXIT_FAILURE);
	}

	if (strstr(lid_state, "open") != NULL) {
		laptop.lid.state = 1;
	} else if (strstr(lid_state, "closed") != NULL) {
		laptop.lid.state = 0;
	}
	return 0;
}

void plug_initialize() {
	plug_connect();

	if (laptop.plug.online) {
		check_plug_state();
	} else {
		fprintf(stderr, "WARNING: Could not connect to plug %s. Disabling functionality.\n", laptop.plug.name);
		fflush(stdout);
	}
}

void plug_connect() {
	strcpy(laptop.plug.name, cfg.devs.plug);

	if (laptop.plug.name[0] == '\0') {
		laptop.plug.online = 0;
		return;
	}
	join_paths(laptop.plug.dir, 2, DEF_PLUG_DIR, laptop.plug.name);

	DIR * dir = opendir(laptop.plug.dir);

	if (dir) {
		closedir(dir);
		laptop.plug.online = 1;
		plug_init_paths();
	} else if (ENOENT == errno) {
		laptop.plug.online = 0;
	} else {
		// opendir() failed for some other reason.
		fprintf(stderr, "ERROR: Could not connect to plug %s: %s\n", laptop.plug.name, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void plug_init_paths() {
	join_paths(laptop.plug.files.state, 2, laptop.plug.dir, DEF_PLUG_STATE_FNAME);
}

int check_plug_state() {
	int result = read_int(laptop.plug.files.state, &laptop.plug.state);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get plug state.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

