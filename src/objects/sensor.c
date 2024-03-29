/*
 *   autolight: a lightweight ambient light sensor daemon
 *   Copyright (C) 2023 Ari E. Bredall
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
#include <stdio.h> // fopen()
#include <stdlib.h>
#include <string.h>
#include <math.h> // log()
#include <dirent.h>
#include <errno.h>
#include "../cfg.h"
#include "../objects.h"
#include "../math.h"
#include "../io.h"
#include "../debug.h" // debug_print

extern void sensor_initialize();
extern void sensor_connect();
extern void sensor_init_paths();
extern int sensor_init_per();
extern int sensor_update();
extern int sensor_get_bri();
extern int sensor_get_kbd_bri();

void sensor_initialize() {
	sensor_connect();

	if (sensor.online) {
		sensor_init_per();
		sensor_update();
	} else {
		fprintf(stderr, "ERROR: Cannot connect to ALS\n");
		exit(EXIT_FAILURE);
	}
}

void sensor_connect() {
	debug_print("%s\n", "Connecting to ALS...");
	strcpy(sensor.name, cfg.devs.als);

	if (sensor.name[0] == '\0') {
		debug_print("%s\n", "Could not connect to ALS: name not given in cfg. Disabling...");
		sensor.online = 0;
		return;
	}
	join_paths(sensor.dir, 2, DEF_ALS_DIR, sensor.name);

	DIR * dir = opendir(sensor.dir);

	if (dir) {
		closedir(dir);
		debug_print("%s\n", "ALS connected!");
		sensor.online = 1;
		sensor_init_paths();
	} else if (ENOENT == errno) {
		debug_print("Could not connect to ALS %s: path doesn't exist. Disabling...\n", kbd.name);
		sensor.online = 0;
	} else {
		// opendir() failed for some other reason.
		fprintf(stderr, "ERROR: Could not connect to ALS %s: %s\n", sensor.name, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void sensor_init_paths() {
	join_paths(sensor.files.input, 2, sensor.dir, DEF_ALS_LUX_FNAME);
	join_paths(sensor.files.freq, 2, sensor.dir, DEF_ALS_FREQ_FNAME);
}

int sensor_update() {
	unsigned long int lux;
	int result = read_long(sensor.files.input, &lux);
	if (result == EXIT_FAILURE) {
		fprintf(stderr, "ERROR: Could not get ALS lux.\n");
		exit(EXIT_FAILURE);
	}
	debug_print("Current ambient lux: %li\n", lux);
	if (lux < cfg.scales.min_lux) {
		debug_print("Ambient lux less than minimum! Setting to %li\n", cfg.scales.min_lux);
		lux = cfg.scales.min_lux;
	} else if (lux > cfg.scales.max_lux) {
		debug_print("Ambient lux greater than maximum! Setting to %li\n", cfg.scales.max_lux);
		lux = cfg.scales.max_lux;
	}

	sensor.lux = lux;
	return 0;
}

int sensor_get_bri() {
	// We use logspace because humans see logarithmically
	float lux_frac = scale_log(sensor.lux, cfg.scales.min_lux, cfg.scales.max_lux);

	if (!laptop.plug.state) {
		lux_frac *= cfg.scales.bri_unpl_mod;
	}

	int bri=(int)round(exp(log(screen.bri.max)*lux_frac));

	if (bri < screen.bri.min) {
		bri=screen.bri.min;
	}
	else if (bri > screen.bri.max) {
		bri=screen.bri.max;
	}

	return bri;
}

int sensor_get_kbd_bri() {
	// We use logspace because humans see logarithmically
	float lux_frac = scale_log(sensor.lux, cfg.scales.min_lux, cfg.scales.max_lux);

	if (!laptop.plug.state) {
		lux_frac *= (2-cfg.scales.bri_unpl_mod);
	}
	
	int bri=(int)round(kbd.bri.max*(1-lux_frac));

	if (bri < kbd.bri.min) {
		bri=kbd.bri.min;
	}
	else if (bri > kbd.bri.max) {
		bri=kbd.bri.max;
	}

	return bri;
}

int sensor_init_per() {
	if (cfg.als.pol_per == 0) {
		float sensor_freq;
		int result = read_float(sensor.files.freq, &sensor_freq);
		if (result == EXIT_FAILURE) {
			fprintf(stderr, "ERROR: Could not get ALS frequency\n");
			exit(EXIT_FAILURE);
		}
		debug_print("ALS sensor frequency: %f\n", sensor_freq);
		sensor.pol_per=1/sensor_freq;
	} else {
		sensor.pol_per = cfg.als.pol_per;
	}
	return 0;
}

