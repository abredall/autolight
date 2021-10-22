#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include "cfg.h"
#include "../io.h"

extern void config_initialize(char * BIN_PATH);

void config_initialize(char * BIN_PATH) {
	/* We want to get the path of the config relative to where the binary is. However,
	 * argv[0] need not be the absolute path, so we have to check /proc/self/exe */
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

	// Begin parsing of cfg
	read_cfg_str(OPT_SCREEN_DEV, cfg.devs.screen, '\0');
	read_cfg_str(OPT_KBD_DEV, cfg.devs.kbd, '\0');
	read_cfg_str(OPT_PLUG_DEV, cfg.devs.plug, '\0');
	read_cfg_str(OPT_LID_DEV, cfg.devs.lid, '\0');
	read_cfg_str(OPT_ALS_DEV, cfg.devs.als, '\0');

	read_cfg_long(OPT_ALS_MIN_LUX, &cfg.scales.min_lux, DEF_MIN_LUX);
	read_cfg_long(OPT_ALS_MAX_LUX, &cfg.scales.max_lux, DEF_MAX_LUX);

	read_cfg_float(OPT_BRI_UNPL_MOD, &cfg.scales.bri_unpl_mod, DEF_BRI_UNPL_MOD);
	read_cfg_float(OPT_BRI_THRESH_FRAC, &cfg.scales.bri_thresh_frac, DEF_BRI_THRESH_FRAC);
	read_cfg_float(OPT_ALS_POL_PER, &cfg.als.pol_per, DEF_ALS_POL_PER);
}
