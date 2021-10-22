#ifndef CFG_CFG_H
#define CFG_CFG_H
#include <linux/limits.h>

struct Config {
	char fname[PATH_MAX];

	struct {
		char screen[PATH_MAX];
		char kbd[PATH_MAX];
		char lid[PATH_MAX];
		char plug[PATH_MAX];
		char als[PATH_MAX];
	} devs;

	struct {
		unsigned long int min_lux;
		unsigned long int max_lux;
		float bri_thresh_frac;
		float bri_unpl_mod;
	} scales;

	struct {
		float pol_per;
	} als;
} cfg;

extern void config_initialize(char * BIN_PATH);

#define REL_CONFIG_PATH "../etc/autolight.conf"

#define OPT_SCREEN_DEV "screen-device"
#define OPT_KBD_DEV "kbd-device"
#define OPT_PLUG_DEV "plug-device"
#define OPT_LID_DEV "lid-device"
#define OPT_ALS_DEV "als-device"
#define OPT_ALS_MIN_LUX "als-min-lux"
#define OPT_ALS_MAX_LUX "als-max-lux"
#define OPT_ALS_POL_PER "als-polling-period"
#define OPT_BRI_THRESH_FRAC "brightness-threshold-fraction"
#define OPT_BRI_UNPL_MOD "brightness-unplugged-modifier"

#define DEF_MIN_LUX 50
#define DEF_MAX_LUX 1000000
#define DEF_ALS_POL_PER 0
#define DEF_BRI_THRESH_FRAC 0.3
#define DEF_BRI_UNPL_MOD 0.9

#endif
