#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>\n", argv[0]);
        return 0;
    }

    FILE *fPointer;
    fPointer = fopen(argv[1], "r");

    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

	unsigned result;
	char map[256][256];
	int w,h;
	int x,y, dx,dy, dir;
	int gx,gy, ox,oy;	

	for (h=0; fgets(map[h], sizeof map[0], fPointer); h++);
	w = strlen(map[0]) -1;	
	for (gy=0; gy<h; gy++)
	for (gx=0; gx<w; gx++) {
		if (map[gy][gx] == GUARD) {
			goto found;
		}
	}
found:	result = 0;
	for (oy=0; oy<h; oy++)
	for (ox=0; ox<w; ox++) {
		if (map[oy][ox] != EMPTY) {
			continue;
		}
		map[oy][ox] = OBSTACLE;	
		dir = UP;
		x = gx;
		y = gy;
		while (x<w && x>=0 && y<h && y>=0) {
			if (map[y][x] == dir) {
				result++;
				break;
			}
			if (map[y][x] == EMPTY) {
				map[y][x] = dir;
			}
			switch (dir) {
			case UP:    dx= 0; dy=-1; break;
			case RIGHT: dx=+1; dy= 0; break;
			case DOWN:  dx= 0; dy=+1; break;
			case LEFT:  dx=-1; dy= 0; break;
			}
			x+=dx; y+=dy;
			if (map[y][x] == OBSTACLE) {
				x-=dx; y-=dy;
				dir = (dir+1) % _COUNT;
			}
		}
		
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (map[y][x] < _COUNT) {
				map[y][x] = EMPTY;
			}
		}
		map[oy][ox] = EMPTY;
		map[gy][gx] = GUARD;
	}
	printf("%u\n", result);
	return 0;
}
