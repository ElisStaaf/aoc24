#ifndef __DEFS__
#define __DEFS__

#include <string.h>
#include <stdbool.h>

#define MIB (1024 * 1024)

typedef enum : size_t {
	DIR_UP = 0,
	DIR_RIGHT = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
} Movement_Direction;

static size_t directions[4] = {0};

char input[MIB] = {0};
char saved_input[MIB] = {0};

static inline size_t find_char(char find, const char *input) { 
	size_t out = 0;
	while (input[out] != find) out++;
	return out;
}

static inline size_t get_linelen(const char *input) {
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

static inline bool
variation_had_loop(size_t i_to_block)
{
	memcpy(input, saved_input, MIB);

	if (input[i_to_block] == '^') return false;
	input[i_to_block] = '#';
	size_t linelen = get_linelen(input);
	size_t linelen_inclf = linelen + 1;
	size_t max_i = strlen(input);
	directions[0] = -linelen_inclf;
	directions[1] = 1;
	directions[2] = linelen_inclf;
	directions[3] = -1;

	size_t guard_loc = find_char('^', input);

	Movement_Direction dir = DIR_UP;
	
	size_t searched = 0;
	while (input[guard_loc] != '\n' 
	       && guard_loc != 0 
	       && guard_loc < max_i) {
		searched += 1;
		if (input[guard_loc] != 'X') { 
		}
		input[guard_loc] = 'X';

		while (input[guard_loc + directions[dir]] == '#') {
			dir = (Movement_Direction)((dir + 1) % 4);
		}
		guard_loc += directions[dir];

		if (searched == 10000000) return true;
	}
	return false;
}

enum {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	_COUNT,
	EMPTY    = '.',
	OBSTACLE = '#',
	GUARD    = '^',
	VISITED  = 'X',
};

#endif
