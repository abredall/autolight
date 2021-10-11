#ifndef CONFIG_H
#define CONFIG_H

struct Config {
	struct Files {
		char * bri;
		char * max_bri;
		char * plug_state;
		char * lid_state;
		char * als_lux;
		char * als_freq;
	} files;

	struct Scaling {
		unsigned int min_lux;
		unsigned long int max_lux;
		float bri_threshhold_frac;
		float bri_unplugged_modifier;
	} scales;

	struct ALS {
		float pol_per;
	} als;
} cfg;

extern void config_initialize();

#endif
