#ifndef IO_CFG_H
#define IO_CFG_H

extern char * read_cfg_str(char * desired_name, char * DEF_VALUE, int * must_free);
extern int read_cfg_long(char * desired_name, unsigned long int * ret, unsigned long int DEF_VALUE);
extern int read_cfg_float(char * desired_name, float * ret, float DEF_VALUE);

#endif
