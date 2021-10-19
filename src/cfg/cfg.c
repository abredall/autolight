#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include "cfg.h"
#include "../io.h"

void config_initialize(char * BIN_PATH) {
	char BIN_DIR[PATH_MAX];

	memset(BIN_DIR, 0, sizeof(BIN_DIR));
	if (readlink("/proc/self/exe", BIN_DIR, PATH_MAX) == -1) {
		fprintf(stderr, "ERROR: Could not get binary path from /proc/self/exe: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	dirname(BIN_DIR);

	join_paths(cfg.fname, 2, BIN_DIR, REL_CONFIG_PATH);

	char * screen_dev = read_cfg_str("screen-device");
	if (screen_dev == NULL) {
		strcpy(screen_dev, DEF_SCREEN_DEV);
	}

	char * kbd_dev = read_cfg_str("kbd-device");
	if (kbd_dev == NULL) {
		strcpy(kbd_dev, DEF_KBD_DEV);
	}

	char * plug_dev = read_cfg_str("plug-device");
	if (plug_dev == NULL) {
		strcpy(plug_dev, DEF_PLUG_DEV);
	}

	char * lid_dev = read_cfg_str("lid-device");
	if (lid_dev == NULL) {
		strcpy(lid_dev, DEF_LID_DEV);
	}

	char * als_dev = read_cfg_str("als-device");
	if (als_dev == NULL) {
		strcpy(als_dev, DEF_ALS_DEV);
	}

	join_paths(cfg.files.bri, 3, DEF_BACKLIGHT_DIR, screen_dev, DEF_BRI_FNAME);
	join_paths(cfg.files.max_bri, 3, DEF_BACKLIGHT_DIR, screen_dev, DEF_MAX_BRI_FNAME);
	join_paths(cfg.files.kbd_bri, 3, DEF_KBD_DIR, kbd_dev, DEF_KBD_BRI_FNAME);
	join_paths(cfg.files.kbd_max_bri, 3, DEF_KBD_DIR, kbd_dev, DEF_KBD_MAX_BRI_FNAME);
	join_paths(cfg.files.plug_state, 3, DEF_PLUG_DIR, plug_dev, DEF_PLUG_STATE_FNAME);
	join_paths(cfg.files.lid_state, 3, DEF_LID_DIR, lid_dev, DEF_LID_STATE_FNAME);
	join_paths(cfg.files.als_lux, 3, DEF_ALS_DIR, als_dev, DEF_ALS_LUX_FNAME);
	join_paths(cfg.files.als_freq, 3, DEF_ALS_DIR, als_dev, DEF_ALS_FREQ_FNAME);

	free(screen_dev);
	free(kbd_dev);
	free(plug_dev);
	free(lid_dev);
	free(als_dev);

	int result;

	unsigned long int min_lux;
	result = read_cfg_long(OPT_ALS_MIN_LUX, &min_lux);
	if (result != 0) {
		min_lux = DEF_MIN_LUX;
	}

	unsigned long int max_lux;
	result = read_cfg_long(OPT_ALS_MAX_LUX, &max_lux);
	if (result != 0) {
		max_lux = DEF_MAX_LUX;
	}

	float bri_thresh_frac;
	result = read_cfg_float(OPT_BRI_THRESH_FRAC, &bri_thresh_frac);
	if (result != 0) {
		bri_thresh_frac = DEF_BRI_THRESH_FRAC;
	}

	float bri_unpl_mod;
	result = read_cfg_float(OPT_BRI_UNPL_MOD, &bri_unpl_mod);
	if (result != 0) {
		bri_unpl_mod = DEF_BRI_UNPL_MOD;
	}

	float als_pol_per;
	result = read_cfg_float(OPT_ALS_POL_PER, &als_pol_per);
	if (result != 0) {
		als_pol_per = DEF_ALS_POL_PER;
	}

	cfg.scales.min_lux = min_lux;
	cfg.scales.max_lux = max_lux;
	cfg.scales.bri_thresh_frac = bri_thresh_frac;
	cfg.scales.bri_unpl_mod = bri_unpl_mod;

	cfg.als.pol_per = als_pol_per;
}
