#ifndef OBJECTS_SENSOR_H
#define OBJECTS_SENSOR_H

extern void sensor_initialize();
extern int sensor_get_bri();
extern int sensor_get_kbd_bri();
extern int sensor_update();
extern int sensor_init_per();

struct Sensor {
	// Whether autolight can connect to the sensor
	int online;

	long int lux;
	float pol_per;
} sensor;

#endif
