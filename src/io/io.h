#ifndef IO_IO_H
#define IO_IO_H
#include <linux/limits.h>

extern int read_str(char * file_name, char var[PATH_MAX]);
extern int write_int(char * file_name, int input);
extern int read_int(char * file_name, int * var);
extern int read_long(char * file_name, unsigned long int * var);
extern int read_float(char * file_name, float * var);

#endif
