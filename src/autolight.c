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
#define _POSIX_C_SOURCE      199309L
#include <stdio.h>
#include <math.h> // fabs()
#include <time.h> // usleep()
#include "cfg.h"
#include "objects.h"
#include "math.h"

extern void change_brightness();

int main(int argc, char **argv) {
	config_initialize(argv[0]);
	screen_initialize();
	kbd_initialize();
	sensor_initialize();
	laptop_initialize();

	long int pol_per_nsec=1000000000*sensor.pol_per;

	struct timespec onesec = {1, 0};
	struct timespec changing = {0, 50000000};

	while(1) {
		clock_t then = clock();
		check_lid_state();
		if (laptop.lid.state == 1) {
			sensor_update();
			change_brightness();

			// Speed up loop if brightness is changing
			if (screen.bri.ch || kbd.bri.ch) {
				nanosleep(&changing, NULL);
			} else {
				// Otherwise sleep for polling period minus loop runtime
				clock_t now = clock();
				long int sleep_nsec = (long int)(pol_per_nsec-(now - then)/(CLOCKS_PER_SEC*1000000000));
				struct timespec remaining = {sleep_nsec/1000000000, sleep_nsec%1000000000};
				nanosleep(&remaining, NULL);
			}

		} else {
			screen.bri.curr = 0;
			screen_set_bri();
			kbd.bri.curr = 0;
			kbd_set_bri();
			nanosleep(&onesec, NULL);
		}
	}
	
	return 0;
}

void change_brightness() {
	// Determine if we need to adjust the screen brightness
	int screen_bri_old; int screen_bri_new; char change_bri;
	if (screen.online) {
		screen_bri_old = screen.bri.curr;
		screen_bri_new = sensor_get_bri();

		float bri_frac_old = scale_log(screen_bri_old, screen.bri.min, screen.bri.max);
		float bri_frac_new = scale_log(screen_bri_new, screen.bri.min, screen.bri.max);

		float frac_diff=fabs(bri_frac_new-bri_frac_old);

		if (frac_diff > cfg.scales.bri_thresh_frac && !screen.bri.ch) {
			change_bri=1;
		} else if (screen_bri_new != screen_bri_old && screen.bri.ch){
			change_bri=1;
		} else {
			change_bri=0;
		}
	}

	// Determine if we need to adjust the keyboard brightness
	int kbd_bri_old; int kbd_bri_new; char change_kbd_bri;
	if (kbd.online) {
		kbd_bri_old = kbd.bri.curr;
		kbd_bri_new = sensor_get_kbd_bri();

		float kbd_bri_frac_old = scale_lin(kbd_bri_old, kbd.bri.min, kbd.bri.max);
		float kbd_bri_frac_new = scale_lin(kbd_bri_new, kbd.bri.min, kbd.bri.max);

		float frac_kbd_diff = fabs(kbd_bri_frac_new-kbd_bri_frac_old);

		if (frac_kbd_diff > cfg.scales.bri_thresh_frac && !kbd.bri.ch) {
			change_kbd_bri=1;
		} else if (kbd_bri_new != kbd_bri_old && kbd.bri.ch){
			change_kbd_bri=1;
		} else {
			change_kbd_bri=0;
		}
	}

	// Always change the brightness when plug state changes
	if (laptop.plug.online) {
		int plug_state_old = laptop.plug.state;
		check_plug_state();
		int plug_state_new = laptop.plug.state;
		if (plug_state_new != plug_state_old) {
			change_bri=1;
			change_kbd_bri=1;
		}
	}

	// Change screen brightness accordingly
	if (change_bri && screen.online) {
		if (screen_bri_new > screen_bri_old) {
			screen.bri.curr += 1;
		} else if (screen_bri_new < screen_bri_old) {
			screen.bri.curr -= 1;
		} else {
			screen.bri.curr = screen_bri_new;
		}
		screen_set_bri();
		screen.bri.ch = true;
	} else {
		screen.bri.ch = false;
	}

	// Change keyboard brightness accordingly
	if (change_kbd_bri && kbd.online) {
		if (kbd_bri_new > kbd_bri_old) {
			kbd.bri.curr += 1;
		} else if (kbd_bri_new < kbd_bri_old) {
			kbd.bri.curr -= 1;
		} else {
			kbd.bri.curr = kbd_bri_new;
		}
		kbd_set_bri();
		kbd.bri.ch = true;
	} else {
		kbd.bri.ch = false;
	}
}
