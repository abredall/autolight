#include <stdio.h> // fopen()
#include <string.h> // strstr()
#include "../config.h" // cfg
#include "../io.h" // read_from()
#include "laptop.h" // laptop

int check_lid_state() {
	char lid_state[20];

	FILE * fp_lid = fopen(cfg.files.lid_state, "r");
	if (fp_lid == NULL) return 1;
	fgets(lid_state, 19, fp_lid);
	fclose(fp_lid);

	if (strstr(lid_state, "open") != NULL) {
		laptop.lid_state = 1;
	} else if (strstr(lid_state, "closed") != NULL) {
		laptop.lid_state = 0;
	}

	return 0;
}
void check_plug_state() {
	laptop.plug_state = read_from(cfg.files.plug_state);
}

void laptop_check_states() {
	check_lid_state();
	check_plug_state();
}

void laptop_initialize() {
	laptop_check_states();
}
