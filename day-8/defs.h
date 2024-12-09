#ifndef __DEFS__
#define __DEFS__

#include <string.h>
#include <stdint.h>

uint8_t grid[1024][1024] = {0};
size_t grid_ylen = 0;
size_t grid_xlen = 0;

uint8_t anti_grid[1024][1024] = {0};

#define COUNT(a) (sizeof(a) / sizeof((a)[0]))

#define M(i, j) map[(i) & 127][(j) & 127]
#define V(i, j) visit[(i) & 127][(j) & 127]
char map[128][128];
char visit[128][128];
int n;

typedef struct {
    int pairs[8][2];
    int n;
} pair_t;

pair_t pairs[128];

bool mark(int i , int j, int f)
{
    if (!M(i, j) || (V(i, j) & f)) return false;
    V(i, j) |= f;
    return true;
}

int sweep(int* p, int* d, int f)
{
    int cnt = 0;
    int i = p[0], j = p[1];
    while (M(i, j)) {
        if (mark(i, j, f)) cnt++;
        i += d[0];
        j += d[1];
    }
    return cnt;
}
#endif
