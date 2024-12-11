#ifndef __DEFS__
#define __DEFS__

#include <stdio.h>

#define MIB (1024 * 1024)

char input[MIB];
char trails[1024][1024];
size_t trail_xlen = 0;
size_t trail_ylen = 0;
long long int sol = 0;

#endif
