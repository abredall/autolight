#ifndef OBJECTS_KBD_H
#define OBJECTS_KBD_H
#include <stdbool.h>

struct Keyboard {
	// Whether autolight can connect to the keyboard
	int online;

	// Min, max, and current brightness
	int min_bri;
	int max_bri;
	int curr_bri;

	// Whether the brightness is currently changing
	bool ch_bri;

} kbd;


extern void kbd_initialize();
extern int kbd_check_bri();
extern int kbd_set_bri();
#endif
