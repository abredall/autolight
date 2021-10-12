#ifndef SCREEN_H
#define SCREEN_H
#include <stdbool.h>

struct Screen {
	// Min, max, and current brightness
	int min_bri;
	int max_bri;
	int curr_bri;

	// Whether the brightness is currently changing
	bool ch_bri;
} screen;


extern void screen_initialize();
extern int screen_check_bri();
extern int screen_set_bri();
#endif
