/*
 *   autolight: a lightweight ambient light sensor daemon
 *   Copyright (C) 2021 John W. Bredall
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
#include <string.h>
#include <stdarg.h>
#include <linux/limits.h>

void join_paths(char * out, int num, ...) {
	va_list valist;
	int i;

	char buff[PATH_MAX];

	va_start(valist, num);

	strcpy(buff, va_arg(valist, char *));

	for (i = 1; i < num; i++) {
		strcat(strcat(buff, "/"), va_arg(valist, char *));
	}

	strcpy(out, buff);
}
