#ifndef OBJECTS_SENSOR_H
#define OBJECTS_SENSOR_H
#include <linux/limits.h>

extern void sensor_initialize();
extern void sensor_connect();
extern void sensor_init_paths();
extern int sensor_update();
extern int sensor_get_bri();
extern int sensor_get_kbd_bri();

struct Sensor {
	char name[PATH_MAX];
	// Whether autolight can connect to the sensor
	int online;

	char dir[PATH_MAX];
	struct {
		char input[PATH_MAX];
		char freq[PATH_MAX];
	} files;

	// The lux reading from the sensor
	long int lux;

	// How frequently to check the sensor
	float pol_per;
} sensor;

#define DEF_ALS_DIR "/sys/bus/iio/devices"
#define DEF_ALS_LUX_FNAME "in_illuminance_input"
#define DEF_ALS_FREQ_FNAME "in_illuminance_sampling_frequency"

#endif
