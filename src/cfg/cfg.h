#ifndef CFG_CFG_H
#define CFG_CFG_H
#include <linux/limits.h>

struct Config {
	char fname[PATH_MAX];

	struct Files {
		char bri[PATH_MAX];
		char max_bri[PATH_MAX];
		char plug_state[PATH_MAX];
		char lid_state[PATH_MAX];
		char als_lux[PATH_MAX];
		char als_freq[PATH_MAX];
	} files;

	struct Scaling {
		unsigned int min_lux;
		unsigned long int max_lux;
		float bri_thresh_frac;
		float bri_unpl_mod;
	} scales;

	struct ALS {
		float pol_per;
	} als;
} cfg;

extern void config_initialize(char * BIN_PATH);

#define REL_CONFIG_PATH "../etc/autolight.conf"

#define OPT_SCREEN_DEV "screen-device"
#define OPT_PLUG_DEV "plug-device"
#define OPT_LID_DEV "lid-device"
#define OPT_ALS_DEV "als-device"
#define OPT_ALS_MIN_LUX "als-min-lux"
#define OPT_ALS_MAX_LUX "als-max-lux"
#define OPT_ALS_POL_PER "als-polling-period"
#define OPT_BRI_THRESH_FRAC "brightness-threshold-fraction"
#define OPT_BRI_UNPL_MOD "brightness-unplugged-modifier"

#define DEF_SCREEN_DEV "acpi_video0"
#define DEF_PLUG_DEV "ADP1"
#define DEF_LID_DEV "LID0"
#define DEF_ALS_DEV "iio:device0"

#define DEF_BACKLIGHT_DIR "/sys/class/backlight"
#define DEF_PLUG_DIR "/sys/class/power_supply"
#define DEF_LID_DIR "/proc/acpi/button/lid"
#define DEF_ALS_DIR "/sys/bus/iio/devices"

#define DEF_BRI_FNAME "brightness"
#define DEF_MAX_BRI_FNAME "max_brightness"
#define DEF_PLUG_STATE_FNAME "online"
#define DEF_LID_STATE_FNAME "state"
#define DEF_ALS_LUX_FNAME "in_illuminance_input"
#define DEF_ALS_FREQ_FNAME "in_illuminance_sampling_frequency"

#define DEF_MIN_LUX 50
#define DEF_MAX_LUX 1000000
#define DEF_ALS_POL_PER 0
#define DEF_BRI_THRESH_FRAC 0.3
#define DEF_BRI_UNPL_MOD 0.9

#endif
