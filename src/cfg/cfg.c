#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include "cfg.h"
#include "../io.h"

void config_initialize(char * BIN_PATH) {
	/* We want to get the path of the config relative to where the binary is. However,
	 * args[0] need not be the absolute path, so we have to check /proc/self/exe */
	char BIN_DIR[PATH_MAX];

	memset(BIN_DIR, 0, sizeof(BIN_DIR));
	if (readlink("/proc/self/exe", BIN_DIR, PATH_MAX) == -1) {
		fprintf(
			stderr, "ERROR: Could not get binary path from /proc/self/exe: %s\n",
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}

	dirname(BIN_DIR);

	join_paths(cfg.fname, 2, BIN_DIR, REL_CONFIG_PATH);

	/* All options read from cfg file */
	char * screen_dev; char * kbd_dev; char * lid_dev; char * plug_dev; char * als_dev;
	unsigned long int min_lux; unsigned long int max_lux;
	float bri_thresh_frac; float bri_unpl_mod; float als_pol_per;

	/* If the string is read from the cfg file, we'll have to free it from memory.
	 * However, if we end up using the default value, there's nothing to free. So
	 * we need to keep track of that. */
	int must_free;

	screen_dev = read_cfg_str("screen-device", DEF_SCREEN_DEV, &must_free);
	join_paths(cfg.files.bri, 3, DEF_BACKLIGHT_DIR, screen_dev, DEF_BRI_FNAME);
	join_paths(cfg.files.max_bri, 3, DEF_BACKLIGHT_DIR, screen_dev, DEF_MAX_BRI_FNAME);
	if (must_free) {
		free(screen_dev);
	}

	kbd_dev = read_cfg_str("kbd-device", DEF_KBD_DEV, &must_free);
	join_paths(cfg.files.kbd_bri, 3, DEF_KBD_DIR, kbd_dev, DEF_KBD_BRI_FNAME);
	join_paths(cfg.files.kbd_max_bri, 3, DEF_KBD_DIR, kbd_dev, DEF_KBD_MAX_BRI_FNAME);
	if (must_free) {
		free(kbd_dev);
	}

	plug_dev = read_cfg_str("plug-device", DEF_PLUG_DEV, &must_free);
	join_paths(cfg.files.plug_state, 3, DEF_PLUG_DIR, plug_dev, DEF_PLUG_STATE_FNAME);
	if (must_free) {
		free(plug_dev);
	}

	lid_dev = read_cfg_str("lid-device", DEF_LID_DEV, &must_free);
	join_paths(cfg.files.lid_state, 3, DEF_LID_DIR, lid_dev, DEF_LID_STATE_FNAME);
	if (must_free) {
		free(lid_dev);
	}

	als_dev = read_cfg_str("als-device", DEF_ALS_DEV, &must_free);
	join_paths(cfg.files.als_lux, 3, DEF_ALS_DIR, als_dev, DEF_ALS_LUX_FNAME);
	join_paths(cfg.files.als_freq, 3, DEF_ALS_DIR, als_dev, DEF_ALS_FREQ_FNAME);
	if (must_free) {
		free(als_dev);
	}

	read_cfg_long(OPT_ALS_MIN_LUX, &min_lux, DEF_MIN_LUX);
	cfg.scales.min_lux = min_lux;

	read_cfg_long(OPT_ALS_MAX_LUX, &max_lux, DEF_MAX_LUX);
	cfg.scales.max_lux = max_lux;

	read_cfg_float(OPT_BRI_THRESH_FRAC, &bri_thresh_frac, DEF_BRI_THRESH_FRAC);
	cfg.scales.bri_thresh_frac = bri_thresh_frac;

	read_cfg_float(OPT_BRI_UNPL_MOD, &bri_unpl_mod, DEF_BRI_UNPL_MOD);
	cfg.scales.bri_unpl_mod = bri_unpl_mod;

	read_cfg_float(OPT_ALS_POL_PER, &als_pol_per, DEF_ALS_POL_PER);
	cfg.als.pol_per = als_pol_per;
}
