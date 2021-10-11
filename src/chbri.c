#include <math.h>   // log(), exp(), and fabs()
#include <stdbool.h> // bool
#include <stdio.h>
#include "objects.h"
#include "config.h"
#include "misc.h"

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

void change_brightness() {
	int bri_old = screen.curr_bri;
	float bri_frac_old = scale_log(bri_old, screen.min_bri, screen.max_bri);

	sensor_update();
	int bri_new = sensor_get_bri();
	float bri_frac_new = scale_log(bri_new, screen.min_bri, screen.max_bri);

	float frac_diff=fabs(bri_frac_new-bri_frac_old);

	/* if we're not currently changing the brightness, only start if the threshold has been reached */
	char change_bri;
	if (frac_diff > cfg.scales.bri_threshhold_frac && !screen.ch_bri) {
		change_bri=1;
	} else if (bri_new != bri_old && screen.ch_bri){
		change_bri=1;
	} else {
		change_bri=0;
	}

	/* always change the brightness when plugged in or unplugged */
	int plug_state_old = laptop.plug_state;

	check_plug_state();

	int plug_state_new = laptop.plug_state;

	if (plug_state_new != plug_state_old) {
		change_bri=1;
	}

	if (change_bri) {
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
}
