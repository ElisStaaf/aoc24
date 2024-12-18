#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "defs.h"

size_t get_linelen(const char *input) {
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

bool isxmas(size_t idx, const char *cursor, const size_t offset[]) {
	const char ms[2] = { 'M', 'S' };
	for (int i = 0; i < 2; i++) {
		size_t oobcheck = idx + offset[i];
		if (oobcheck < 0 || oobcheck > max_i) return 0;
		if (cursor[offset[i]] != ms[i]) return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>\n", argv[0]);
        return 0;
    }

    FILE *fPointer;
    fPointer = fopen(argv[1], "r");

	fread(input, 1, MIB, fPointer);
	size_t linelen = get_linelen(input);
	size_t linelen_inclf = linelen + 1;
	max_i = strlen(input);

	/* Rather then checking both ways in the function, I am being lazy and
	 * checking both ways by adding both ways to the offsets. 
	 *
	 * EXCEPT after some debugging in part2 it seems that maybe this was 
	 * NOT the best approach*/
	size_t offset1[2] = {
		linelen_inclf + 1,
		-1 * linelen_inclf - 1,
	};
	size_t offset2[2] = {
		-1 * linelen_inclf - 1,
		linelen_inclf + 1,
	};
	size_t offset3[2] = {
		linelen_inclf - 1,
		-1 * linelen_inclf + 1,
	};
	size_t offset4[2] = {
		-1 * linelen_inclf + 1,
		linelen_inclf - 1,
	};

	long long int sol = 0;
	char *cursor = input;
	size_t i = 0;
	while (*cursor) {
		if (*cursor == 'A') {
			bool typea = false;
			if (isxmas(i, cursor, offset1)) typea = true;
			if (isxmas(i, cursor, offset2)) typea = true;
			bool typeb = false;
			if (isxmas(i, cursor, offset3)) typeb = true;
			if (isxmas(i, cursor, offset4)) typeb = true;
			if (typea && typeb) sol += 1;
		}
		cursor++;
		i++;
	}
	printf("%lld\n", sol);
}
