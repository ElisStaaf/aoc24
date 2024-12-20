#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "defs.h"

size_t get_linelen(const char *input) {
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

long long int isxmas(size_t idx, const char *cursor, const size_t offset[]) {
	const char mas[3] = { 'M', 'A', 'S' };
	for (int i = 0; i < 3; i++) {
		size_t oobcheck = idx + offset[1];
		if (oobcheck < 0 || oobcheck > max_i) return 0;
		if (cursor[offset[i]] != mas[i]) return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>\n", argv[0]);
        return 0;
    }

    FILE * fPointer;
    fPointer = fopen(argv[1], "r");

    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

	fread(input, 1, MIB, fPointer);
	size_t linelen = get_linelen(input);
	size_t linelen_inclf = linelen + 1;
	max_i = strlen(input);

	size_t offset1[3] = {
		linelen_inclf - 1,
		2 * linelen_inclf - 2,
		3 * linelen_inclf - 3,
	};
	size_t offset2[3] = {
		linelen_inclf,
		2 * linelen_inclf,
		3 * linelen_inclf,
	};
	size_t offset3[3] = {
		linelen_inclf + 1,
		2 * linelen_inclf + 2,
		3 * linelen_inclf + 3,
	};
	size_t offset4[3] = {
		-1 * linelen_inclf - 1,
		-2 * linelen_inclf - 2,
		-3 * linelen_inclf - 3,
	};
	size_t offset5[3] = {
		-1 * linelen_inclf,
		-2 * linelen_inclf,
		-3 * linelen_inclf,
	};
	size_t offset6[3] = {
		-1 * linelen_inclf + 1,
		-2 * linelen_inclf + 2,
		-3 * linelen_inclf + 3,
	};
	size_t offset7[3] = {1, 2, 3};
	size_t offset8[3] = {-1, -2, -3};

	long long int sol = 0;
	char *cursor = input;
	size_t i = 0;
	while (*cursor) {
		if (*cursor == 'X') {
			sol += isxmas(i, cursor, offset1);
			sol += isxmas(i, cursor, offset2);
			sol += isxmas(i, cursor, offset3);
			sol += isxmas(i, cursor, offset4);
			sol += isxmas(i, cursor, offset5);
			sol += isxmas(i, cursor, offset6);
			sol += isxmas(i, cursor, offset7);
			sol += isxmas(i, cursor, offset8);
		}
		cursor++;
		i++;
	}
	printf("%lld\n", sol);
}
