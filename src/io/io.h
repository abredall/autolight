#ifndef IO_IO_H
#define IO_IO_H

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

extern int read_str(char * file_name, char var[BUFF_SIZE]);
extern int write_int(char * file_name, int input);
extern int read_int(char * file_name, int * var);

#endif
