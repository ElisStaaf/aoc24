#include <stdio.h>
#include <string.h>

#include "defs.h"

size_t get_linelen(const char *input) {
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

void scan_trail(size_t x, size_t y, char curr) {
	if (x < 0 || x >= trail_xlen) return;
	if (y < 0 || y >= trail_ylen) return;
	if (trails[y][x] != curr) return;

	if (trails[y][x] == '9') {
		sol++;
		return;
	}

	scan_trail(x + 1, y, curr + 1);
	scan_trail(x - 1, y, curr + 1);
	scan_trail(x, y + 1, curr + 1);
	scan_trail(x, y - 1, curr + 1);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    FILE* fPointer;
    fPointer = fopen(argv[1], "r");


	char scanbuf[256] = {0};

	while (fgets(scanbuf, sizeof scanbuf, fPointer)) {
		trail_xlen = get_linelen(scanbuf);
		memcpy(trails[trail_ylen], scanbuf, trail_xlen);
		trail_ylen += 1;
		memset(scanbuf, 0, sizeof scanbuf);
	}

	for (size_t x = 0; x < trail_xlen; x++) {
		for (size_t y = 0; y < trail_ylen; y++) {
			scan_trail(x, y, '0');
		}
	}
	printf("%lld\n", sol);
}
