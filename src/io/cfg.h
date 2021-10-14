#ifndef IO_CFG_H
#define IO_CFG_H

extern char * read_cfg_str(char * cfg_name, char * desired_name);
extern int read_cfg_long(char * cfg_name, char * desired_name, unsigned long int * ret);
extern int read_cfg_float(char * cfg_name, char * desired_name, float * ret);

#endif
