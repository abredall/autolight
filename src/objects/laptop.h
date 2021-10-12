#ifndef LAPTOP_H
#define LAPTOP_H

struct Laptop {
	int lid_state;
	int plug_state;
} laptop;

extern void laptop_initialize();
extern int check_plug_state();
extern int check_lid_state();
extern void laptop_check_states();

#endif
