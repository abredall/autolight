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
