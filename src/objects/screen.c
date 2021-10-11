#include <stdbool.h> // bool
#include "../io.h" // read_from(), write_to()
#include "../config.h" // cfg
#include "screen.h" // screen

void screen_check_bri() {
	screen.curr_bri = read_from(cfg.files.bri);
}

void screen_set_bri() {
	write_to(cfg.files.bri, screen.curr_bri);
}

void screen_initialize() {
	screen.min_bri = 1;
	screen.max_bri = read_from(cfg.files.max_bri);
	screen_check_bri();
	screen.ch_bri = false;
}

