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
		if (laptop.lid_state == 1) {
			change_brightness();

			/* speed up loop if brightness is changing */
			if (screen.ch_bri || kbd.ch_bri) {
				nanosleep(&changing, NULL);
			} else {
				/* otherwise sleep for polling period minus loop runtime */
				clock_t now = clock();
				long int sleep_nsec = (long int)(pol_per_nsec-(now - then)/(CLOCKS_PER_SEC*1000000000));
				struct timespec remaining = {sleep_nsec/1000000000, sleep_nsec%1000000000};
				nanosleep(&remaining, NULL);
			}

		} else {
			screen.curr_bri = 0;
			screen_set_bri();
			kbd.curr_bri = 0;
			kbd_set_bri();
			nanosleep(&onesec, NULL);
		}
	}
	
	return 0;
}

void change_brightness() {
	// First, we grab everything we need from the last time the sensor was used
	int bri_old;
	if (screen.online) bri_old = screen.curr_bri;

	int kbd_bri_old;
	if (kbd.online) kbd_bri_old = kbd.curr_bri;

	sensor_update();

	int bri_new;
	if (screen.online) bri_new = sensor_get_bri();

	int kbd_bri_new;
	if (kbd.online) kbd_bri_new = sensor_get_kbd_bri();

	char change_bri;
	if (screen.online) {
		float bri_frac_old = scale_log(bri_old, screen.min_bri, screen.max_bri);
		float bri_frac_new = scale_log(bri_new, screen.min_bri, screen.max_bri);

		float frac_diff=fabs(bri_frac_new-bri_frac_old);

		if (frac_diff > cfg.scales.bri_thresh_frac && !screen.ch_bri) {
			change_bri=1;
		} else if (bri_new != bri_old && screen.ch_bri){
			change_bri=1;
		} else {
			change_bri=0;
		}
	}

	char change_kbd_bri;
	if (kbd.online) {
		float kbd_bri_frac_old = scale_lin(kbd_bri_old, kbd.min_bri, kbd.max_bri);
		float kbd_bri_frac_new = scale_lin(kbd_bri_new, kbd.min_bri, kbd.max_bri);

		float frac_kbd_diff = fabs(kbd_bri_frac_new-kbd_bri_frac_old);

		if (frac_kbd_diff > cfg.scales.bri_thresh_frac && !kbd.ch_bri) {
			change_kbd_bri=1;
		} else if (kbd_bri_new != kbd_bri_old && kbd.ch_bri){
			change_kbd_bri=1;
		} else {
			change_kbd_bri=0;
		}
	}

	// Always change the brightness when plugged in or unplugged
	if (laptop.plug_online) {
		int plug_state_old = laptop.plug_state;
		check_plug_state();
		int plug_state_new = laptop.plug_state;
		if (plug_state_new != plug_state_old) {
			change_bri=1;
			change_kbd_bri=1;
		}
	}

	if (change_bri && screen.online) {
		if (bri_new > bri_old) {
			screen.curr_bri += 1;
		} else if (bri_new < bri_old) {
			screen.curr_bri -= 1;
		} else {
			screen.curr_bri = bri_new;
		}
		screen_set_bri();
		screen.ch_bri = true;
	} else {
		screen.ch_bri = false;
	}

	if (change_kbd_bri && kbd.online) {
		if (kbd_bri_new > kbd_bri_old) {
			kbd.curr_bri += 1;
		} else if (kbd_bri_new < kbd_bri_old) {
			kbd.curr_bri -= 1;
		} else {
			kbd.curr_bri = kbd_bri_new;
		}
		kbd_set_bri();
		kbd.ch_bri = true;
	} else {
		kbd.ch_bri = false;
	}
}
