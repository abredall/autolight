#include <stdio.h> // fopen()
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h> // log()
#include "../config.h"
#include "sensor.h"
#include "laptop.h"
#include "screen.h"
#include "../misc.h"

int sensor_update() {
	long int lux;
	FILE * fp_lux = fopen(cfg.files.als_lux, "r");
	if (fp_lux == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", cfg.files.als_lux, strerror(errno));
		fprintf(stderr, "ERROR: Could not get lux reading from ALS\n");
		exit(EXIT_FAILURE);
	}
	if (fscanf(fp_lux, "%li", &lux) != 1) return 1;
	fclose (fp_lux);

	if (lux < cfg.scales.min_lux) {
		lux = cfg.scales.min_lux;
	} else if (lux > cfg.scales.max_lux) {
		lux = cfg.scales.max_lux;
	}

	sensor.lux = lux;
	return 0;
}

int sensor_get_bri() {
	/* we use logspace because humans see logarithmically */
	float lux_frac = scale_log(sensor.lux, cfg.scales.min_lux, cfg.scales.max_lux);

	if (!laptop.plug_state) {
		lux_frac *= cfg.scales.bri_unplugged_modifier;
	}

	int bri=(int)round(exp(log(screen.max_bri)*lux_frac));

	if (bri < screen.min_bri) {
		bri=screen.min_bri;
	}
	else if (bri > screen.max_bri) {
		bri=screen.max_bri;
	}

	return bri;
}

int sensor_init_per() {
	if (cfg.als.pol_per == 0) {
		float sensor_freq;

		FILE * fp_sens = fopen(cfg.files.als_freq, "r");
		if (fp_sens == NULL) {
			fprintf(stderr, "ERROR: Could not open %s: %s\n", cfg.files.als_freq, strerror(errno));
			fprintf(stderr, "ERROR: Could not get ALS frequency\n");
			exit(EXIT_FAILURE);
		}
		if (fscanf(fp_sens, "%f", &sensor_freq) != 1) return 1;
		fclose(fp_sens);
		sensor.pol_per=1/sensor_freq;
	} else {
		sensor.pol_per = cfg.als.pol_per;
	}
	return 0;
}

void sensor_initialize() {
	sensor_init_per();
	sensor_update();
}
