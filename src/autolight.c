#include <stdio.h>  // printf(), fopen(), fprintf(), etc.
#include <stdlib.h> // atoi(), atof()
#include <string.h>
#include <unistd.h> // sleep()
#include <math.h>   // log(), exp(), and fabs()
#include "io.h"
#include "config.h"

const int MIN_BRI=1;
int MAX_BRI;

int AMBI_BRI_OLD;
int PLUG_STATE_OLD;

int change_brightness(long int lux) {
	if (lux < MIN_LUX) {
		lux = MIN_LUX;
	} else if (lux > MAX_LUX) {
		lux = MAX_LUX;
	}

	float ambi_bri_frac = (log(lux)-log(MIN_LUX))/(log(MAX_LUX)-log(MIN_LUX));
	int plug_state = read_from(PLUG_STATE_FILE);
	if (!plug_state) {
		ambi_bri_frac *= BRI_UNPLUGGED_MODIFIER;
	}

	float ambi_bri_frac_old = (log(AMBI_BRI_OLD)-log(MIN_LUX))/(log(MAX_LUX)-log(MIN_LUX));
	float frac_diff=fabs(ambi_bri_frac-ambi_bri_frac_old);

	char change_bri;
	if (frac_diff < BRI_THRESHOLD_FRAC) {
		change_bri=0;
	} else {
		change_bri=1;
	}

	if (plug_state != PLUG_STATE_OLD) {
		change_bri=1;
	}

	int ambi_bri=(int)exp(log(MAX_BRI)*ambi_bri_frac);
	if (ambi_bri < 0) ambi_bri=0;
	if (ambi_bri > MAX_BRI) ambi_bri=MAX_BRI;

	/* printf("%i\n", ambi_bri); */
	/* fflush(stdout); */
	if (change_bri) write_to(BRI_FILE, ambi_bri);

	AMBI_BRI_OLD=ambi_bri;
	PLUG_STATE_OLD=plug_state;

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

	char lid_state[7];
	long lux;
	while(1) {
		sleep(POLLING_PER);
		FILE * fp_lid = fopen(LID_STATE_FILE, "r");
		if (fp_lid == NULL) return 1;
		fgets(lid_state, 19, fp_lid);
		fclose(fp_lid);
		if (strstr(lid_state, "open") != NULL) {
			FILE * fp_lux = fopen("/sys/bus/iio/devices/iio:device0/in_illuminance_input", "r");
			if (fp_lux == NULL) return 1;
			if (fscanf(fp_lux, "%li", &lux) != 1) return 1;
			fclose(fp_lux);
			change_brightness(lux);
			fflush(stdout);
		}
	}
	
	return 0;
}
