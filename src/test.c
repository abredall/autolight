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
#include <stdio.h>
#include "objects/test.h"
#include "cfg.h"

int main(int argc, char **argv) {
	config_initialize(argv[0]);
	int n_pass = 0, n_fail = 0;
	test_objects(&n_pass, &n_fail);
	printf("Passed: %d\tFailed: %d\n", n_pass, n_fail);

	return 0;
}
