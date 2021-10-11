#ifndef SENSOR_H
#define SENSOR_H

extern void sensor_initialize();
extern int sensor_get_bri();
extern int sensor_update();

struct Sensor {
	long int lux;
	float pol_per;
} sensor;

#endif
