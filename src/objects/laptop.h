#ifndef OBJECTS_LAPTOP_H
#define OBJECTS_LAPTOP_H
#include <linux/limits.h>

extern void laptop_initialize();
extern void lid_initialize();
extern void lid_connect();
extern void lid_init_paths();
extern int check_lid_state();
extern void plug_initialize();
extern void plug_connect();
extern void plug_init_paths();
extern int check_plug_state();

struct Laptop {
	struct {
		char name[PATH_MAX];
		// Whether autolight can connect to the lid or plug
		int online;
	
		char dir[PATH_MAX];
		struct {
			char state[PATH_MAX];
		} files;
	
		int state;
	} lid, plug;
} laptop;

#define DEF_LID_DIR "/proc/acpi/button/lid"
#define DEF_PLUG_DIR "/sys/class/power_supply"
#define DEF_PLUG_STATE_FNAME "online"
#define DEF_LID_STATE_FNAME "state"

#endif
