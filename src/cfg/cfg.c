#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cfg.h"
#include "../io.h"

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

// TODO: Make all of these read from a config
// TODO: Add multi-monitor support


void config_initialize() {
	char cfg_name[BUFF_SIZE];
	strcat(strcpy(cfg_name, getenv("HOME")), "/.config/autolight/autolight.conf");
	
	char * screen_dev = read_cfg_str(cfg_name, "screen-device");
	if (screen_dev == NULL) {
		strcpy(screen_dev, "acpi_video0");
	}
	char * plug_dev = read_cfg_str(cfg_name, "plug-device");
	if (plug_dev == NULL) {
		strcpy(plug_dev, "ADP1");
	}
	char * lid_dev = read_cfg_str(cfg_name, "lid-device");
	if (lid_dev == NULL) {
		strcpy(lid_dev, "LID0");
	}
	char * als_dev = read_cfg_str(cfg_name, "als-device");
	if (als_dev == NULL) {
		strcpy(als_dev, "iio:device0");
	}

	char * backlight_dir = "/sys/class/backlight/";
	char * plug_dir = "/sys/class/power_supply/";
	char * lid_dir = "/proc/acpi/button/lid/";
	char * als_dir = "/sys/bus/iio/devices/";

	char bri_file[BUFF_SIZE];
	strcat(strcat(strcpy(bri_file, backlight_dir), screen_dev), "/brightness");

	char max_bri_file[BUFF_SIZE];
	strcat(strcat(strcpy(max_bri_file, backlight_dir), screen_dev), "/max_brightness");

	char plug_state_file[BUFF_SIZE];
	strcat(strcat(strcpy(plug_state_file, plug_dir), plug_dev), "/online");

	char lid_state_file[BUFF_SIZE];
	strcat(strcat(strcpy(lid_state_file, lid_dir), lid_dev), "/state");

	char als_lux_file[BUFF_SIZE];
	strcat(strcat(strcpy(als_lux_file, als_dir), als_dev), "/in_illuminance_input");

	char als_freq_file[BUFF_SIZE];
	strcat(strcat(strcpy(als_freq_file, als_dir), als_dev), "/in_illuminance_sampling_frequency");

	cfg.files.bri = bri_file;
	cfg.files.max_bri = max_bri_file;
	cfg.files.plug_state = plug_state_file;
	cfg.files.lid_state = lid_state_file;
	cfg.files.als_lux = als_lux_file;
	cfg.files.als_freq = als_freq_file;

	unsigned long int min_lux; unsigned long int max_lux;
	float bri_thresh_frac; float bri_unpl_mod; float als_pol_per;

	int result;

	result = read_cfg_long(cfg_name, "als-min-lux", &min_lux);
	if (result != 0) {
		min_lux = 50;
	}
	result = read_cfg_long(cfg_name, "als-max-lux", &max_lux);
	if (result != 0) {
		max_lux = 1000000;
	}
	result = read_cfg_float(cfg_name, "als-polling-period", &als_pol_per);
	if (result != 0) {
		als_pol_per = 0;
	}
	result = read_cfg_float(cfg_name, "brightness-threshold-fraction", &bri_thresh_frac);
	if (result != 0) {
		bri_thresh_frac = 0.3;
	}
	result = read_cfg_float(cfg_name, "brightness-unplugged-modifier", &bri_unpl_mod);
	if (result != 0) {
		bri_unpl_mod = 0.9;
	}


	cfg.scales.min_lux = min_lux;
	cfg.scales.max_lux = max_lux;
	cfg.scales.bri_threshhold_frac = bri_thresh_frac;
	cfg.scales.bri_unplugged_modifier = bri_unpl_mod;

	cfg.als.pol_per = als_pol_per;
	
}
