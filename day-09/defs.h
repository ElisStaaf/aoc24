#ifndef __DEFS__
#define __DEFS__

#include <stdio.h>
#include <string.h>

char buf[20000 + 1];
int map[200000];
int n;

void printmap()
{
    for (int i = 0; i < n; i++) {
        if (map[i] >= 0) {
            printf("%d", map[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

#endif
