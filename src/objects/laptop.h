#ifndef OBJECTS_LAPTOP_H
#define OBJECTS_LAPTOP_H

struct Laptop {
	int lid_state;
	int plug_state;

	// Whether autolight can connect to the lid or adapter
	int lid_online;
	int plug_online;
} laptop;

extern void laptop_initialize();
extern int check_plug_state();
extern int check_lid_state();
extern void laptop_check_states();

#endif
