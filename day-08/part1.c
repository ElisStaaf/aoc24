#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

static inline size_t get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

static inline void add_antis(size_t o_x, size_t o_y)
{
	uint8_t o_symbol = grid[o_y][o_x];
	if (o_symbol == '.') return;

	for (size_t x = 0; x < grid_xlen; x++) {
		for (size_t y = 0; y < grid_ylen; y++) {
			if (x == o_x && y == o_y) return;
			uint8_t symbol = grid[y][x];
			if (symbol != o_symbol) continue;

			size_t xdiff = o_x - x;
			size_t ydiff = o_y - y;

			if (o_y > 0 && o_x > 0 
			    && anti_grid[o_y + ydiff][o_x + xdiff] 
			    != '\0')
				anti_grid[o_y + ydiff][o_x + xdiff] = '#';

			if (y > 0 && x > 0 
			    && anti_grid[y - ydiff][x - xdiff] 
			    != '\0')
				anti_grid[y - ydiff][x - xdiff] = '#';
		}
	}
	return;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    FILE* fPointer;
    fPointer = fopen(argv[1], "r");

	char scanbuf[256] = {0};
	while (fgets(scanbuf, sizeof scanbuf, fPointer)) {
		if (!grid_xlen) grid_xlen = get_linelen(scanbuf);
		memcpy(grid[grid_ylen], scanbuf, grid_xlen);
		grid_ylen++;
		memset(scanbuf, 0, sizeof scanbuf);
	}
    memcpy(anti_grid, grid, sizeof grid);
	for (int x = 0; x < grid_xlen; x++) {
		for (int y = 0; y < grid_ylen; y++) add_antis(x, y);
	}
	long long int sol = 0;

	for (int x = 0; x < grid_xlen; x++) {
		for (int y = 0; y < grid_ylen; y++) {
			if (anti_grid[y][x] == '#') sol += 1;
		}
	}
	printf("%llu\n", sol);
}
