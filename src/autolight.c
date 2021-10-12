#include <stdio.h>  // fopen(), fprintf(), etc.
#include <stdbool.h> // bool
#define _BSD_SOURCE // fixed usleep import
#include <time.h> // usleep()
#include <string.h> // strstr()
#include <unistd.h> // sleep()
#include "config.h"
#include "objects.h"
#include "chbri.h"

int main() {
	config_initialize();
	screen_initialize();
	sensor_initialize();
	laptop_initialize();

	long int pol_per_usec=1000000*sensor.pol_per;

	while(1) {
		clock_t then = clock();
		check_lid_state();
		if (laptop.lid_state == 1) {
			change_brightness();

			/* speed up loop if brightness is changing */
			if (screen.ch_bri) {
				usleep(0.05*1000000);
			} else {
				/* otherwise sleep for polling period minus loop runtime */
				clock_t now = clock();
				long sleep_usec = (long int)(pol_per_usec-(now - then)/(CLOCKS_PER_SEC*1000000));
				usleep(sleep_usec);
			}

		} else {
			screen.curr_bri = 0;
			screen_set_bri();
			usleep(1000000);
		}
	}
	
	return 0;
}
