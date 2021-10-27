/*
 *   Copyright 2021 John W. Bredall
 *
 *   This file is part of autolight.
 *
 *   autolight is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   autolight is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with autolight.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "laptop.h"
#include "sensor.h"
#include "screen.h"
#include "kbd.h"
#include <stdio.h>

int test_objects(int * n_pass, int * n_fail) {
	test_laptop(n_pass, n_fail);
	test_kbd(n_pass, n_fail);
	test_sensor(n_pass, n_fail);
	test_screen(n_pass, n_fail);

	return 0;
}
