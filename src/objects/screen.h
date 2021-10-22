#ifndef OBJECTS_SCREEN_H
#define OBJECTS_SCREEN_H
#include <stdbool.h>
#include <linux/limits.h>

extern void screen_initialize();
extern void screen_connect();
extern void screen_init_paths();
extern int screen_get_bri();
extern int screen_set_bri();
extern int screen_get_max_bri();

struct Screen {
	char name[PATH_MAX];
	// Whether autolight can connect to the screen
	int online;

	char dir[PATH_MAX];
	struct {
		char bri[PATH_MAX];
		char max_bri[PATH_MAX];
	} files;

	// Min, max, and current brightness
	struct{
		int min;
		int max;
		int curr;
		// Whether the brightness is currently changing
		bool ch;
	} bri;
} screen;

#define DEF_SCREEN_DIR "/sys/class/backlight"
#define DEF_SCREEN_BRI_FNAME "brightness"
#define DEF_SCREEN_MAX_BRI_FNAME "max_brightness"

#endif
