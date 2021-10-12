#include "config.h"
// TODO: Make all of these read from a config
// TODO: Add multi-monitor support
void config_initialize() {
	cfg.files.bri = "/sys/class/backlight/acpi_video0/brightness";
	cfg.files.max_bri = "/sys/class/backlight/acpi_video0/max_brightness";
	cfg.files.plug_state = "/sys/class/power_supply/ADP1/online";
	cfg.files.lid_state = "/proc/acpi/button/lid/LID0/state";
	cfg.files.als_lux = "/sys/bus/iio/devices/iio:device0/in_illuminance_input";
	cfg.files.als_freq = "/sys/bus/iio/devices/iio:device0/in_illuminance_sampling_frequency";

	cfg.scales.min_lux = 50;
	cfg.scales.max_lux = 1000000;
	cfg.scales.bri_threshhold_frac = 0.3;
	cfg.scales.bri_unplugged_modifier = 0.9;

	cfg.als.pol_per = 0;
}
