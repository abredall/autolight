#include <stdio.h>  // printf(), fopen(), fprintf(), etc.
#include <string.h> // strstr()
#define _BSD_SOURCE // fixed usleep import
#include <unistd.h> // sleep()
#include <math.h>   // log(), exp(), and fabs()
#include <time.h>
#include "io.h"
#include "config.h"

const int MIN_BRI=1;
int MAX_BRI;

int AMBI_BRI_OLD;
int PLUG_STATE_OLD;
int CHANGING_BRI=0;

/* 
 * Change screen brightness based on input lux value
 * 
 * Parameters 
 * ========== 
 * lux:		A lux value, i.e. from an Ambient Light Sensor (ALS)
 * 
 * Returns 
 * ======= 
 * Truth value of if brightness has changed (1 if changed, 0 otherwise)
 * 
 */ 
int change_brightness(long int lux) {
	if (lux < MIN_LUX) {
		lux = MIN_LUX;
	} else if (lux > MAX_LUX) {
		lux = MAX_LUX;
	}

	/* we use logspace because humans see logarithmically */
	float ambi_bri_frac = (log(lux)-log(MIN_LUX))/(log(MAX_LUX)-log(MIN_LUX));

	int plug_state = read_from(PLUG_STATE_FILE);
	if (!plug_state) {
		ambi_bri_frac *= BRI_UNPLUGGED_MODIFIER;
	}

	int ambi_bri=(int)round(exp(log(MAX_BRI)*ambi_bri_frac));
	if (ambi_bri < 0) ambi_bri=0;
	if (ambi_bri > MAX_BRI) ambi_bri=MAX_BRI;

	float ambi_bri_frac_old = (log(AMBI_BRI_OLD)-log(MIN_BRI))/(log(MAX_BRI)-log(MIN_BRI));
	float frac_diff=fabs(ambi_bri_frac-ambi_bri_frac_old);

	/* if we're not currently changing the brightness, only start if the threshold has been reached */
	char change_bri;
	if (frac_diff > BRI_THRESHOLD_FRAC && CHANGING_BRI == 0) {
		change_bri=1;
	} else if (AMBI_BRI_OLD != ambi_bri && CHANGING_BRI == 1){
		change_bri=1;
	} else {
		change_bri=0;
	}

	/* always change the brightness when plugged in or unplugged */
	if (plug_state != PLUG_STATE_OLD) {
		change_bri=1;
		PLUG_STATE_OLD=plug_state;
	}

	if (change_bri) {
		if (AMBI_BRI_OLD < ambi_bri) {
			AMBI_BRI_OLD += 1;
		} else if (AMBI_BRI_OLD > ambi_bri) {
			AMBI_BRI_OLD -= 1;
		} else {
			AMBI_BRI_OLD = ambi_bri;
		}
		write_to(BRI_FILE, AMBI_BRI_OLD);
		return 1;
	}

	return 0;
}

int main() {
	MAX_BRI=read_from(MAX_BRI_FILE);
	AMBI_BRI_OLD=read_from(BRI_FILE);
	PLUG_STATE_OLD=read_from(PLUG_STATE_FILE);

	if (POLLING_PER == 0) {
		float sensor_freq;

		FILE * fp_sens = fopen("/sys/bus/iio/devices/iio:device0/in_illuminance_sampling_frequency", "r");
		if (fp_sens == NULL) return 1;
		if (fscanf(fp_sens, "%f", &sensor_freq) != 1) return 1;
		fclose(fp_sens);

		POLLING_PER=1/sensor_freq;
	}

	long int pol_per_usec=1000000*POLLING_PER;

	char lid_state[7];
	long lux;

	while(1) {
		clock_t then = clock();

		/* make sure laptop lid is open */
		FILE * fp_lid = fopen(LID_STATE_FILE, "r");
		if (fp_lid == NULL) return 1;
		fgets(lid_state, 19, fp_lid);
		fclose(fp_lid);

		if (strstr(lid_state, "open") != NULL) {
			/* read in lux value */
			FILE * fp_lux = fopen("/sys/bus/iio/devices/iio:device0/in_illuminance_input", "r");
			if (fp_lux == NULL) return 1;
			if (fscanf(fp_lux, "%li", &lux) != 1) return 1;
			fclose(fp_lux);

			CHANGING_BRI=change_brightness(lux);

			/* speed up loop if brightness is changing */
			if (CHANGING_BRI == 1) {
				usleep(0.05*1000000);
			} else {
				/* otherwise sleep for polling period minus loop runtime */
				clock_t now = clock();
				long sleep_usec = (long int)(pol_per_usec-(now - then)/(CLOCKS_PER_SEC*1000000));
				usleep(sleep_usec);
			}

		} else {
			/* if laptop lid is closed, only check once per second to save battery */
			usleep(1000000);
		}
	}
	
	return 0;
}
