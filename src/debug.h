#ifndef DEBUG_H
#define DEBUG_H
#include "args.h"

#define debug_print(fmt, ...) \
        do { if (args.debug) fprintf(stderr, "%s:%s(): " fmt, __FILE__, \
                                __func__, __VA_ARGS__); } while (0)

#endif
