#include <stdio.h>
#include <stdint.h>

#include "defs.h"

int main(int argc, char **argv) {
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

	fread(input, 1, MIB, fPointer);

	long long int sol = 0;
	size_t linelen = get_linelen(input);
	size_t linelen_inclf = linelen + 1;
	size_t max_i = strlen(input);
	directions[0] = -linelen_inclf;
	directions[1] = 1;
	directions[2] = linelen_inclf;
	directions[3] = -1;

	size_t guard_loc = find_char('^', input);

	Movement_Direction dir = DIR_UP;

	while (input[guard_loc] != '\n' 
	       && guard_loc != 0 
	       && guard_loc < max_i) {
		if (input[guard_loc] != 'X') sol += 1;
		input[guard_loc] = 'X';

		while (input[guard_loc + directions[dir]] == '#') {
			dir = (dir + 1) % 4;
			printf("-*- another step -*-\n%s", input);
		}
		guard_loc += directions[dir];
	}
	printf("-*- another step -*-\n%s", input);
	printf("%lld\n", sol);
}
