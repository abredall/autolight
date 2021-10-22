#ifndef OBJECTS_KBD_H
#define OBJECTS_KBD_H
#include <stdbool.h>
#include <linux/limits.h>

extern void kbd_initialize();
extern void kbd_connect();
extern int kbd_get_bri();
extern int kbd_set_bri();
extern int kbd_get_max_bri();

struct Keyboard {
	char name[PATH_MAX];
	// Whether autolight can connect to the keyboard
	int online;

	char dir[PATH_MAX];
	struct {
		char bri[PATH_MAX];
		char max_bri[PATH_MAX];
	} files;

	// Min, max, and current brightness
	struct {
		int min;
		int max;
		int curr;
		// Whether the brightness is currently changing
		bool ch;
	} bri;

} kbd;

#define DEF_KBD_DIR "/sys/class/leds"
#define DEF_KBD_BRI_FNAME "brightness"
#define DEF_KBD_MAX_BRI_FNAME "max_brightness"

#endif
