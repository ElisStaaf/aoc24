#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "defs.h"


struct mapval get_cache(long long int key, long long int depth);

void cache(long long int key, long long int val, long long int depth);

struct pair_optional has_even_digits(long long int x);

long long int calculate_stones(long long int n, size_t depth);

struct pair_optional has_even_digits(long long int x) {
	char buf[128] = {0};
	sprintf(buf, "%lld", x);

	size_t buflen = strlen(buf);
	if (buflen % 2 == 0) {
		char lbuf[64] = {0};
		char rbuf[64] = {0};
		memcpy(lbuf, buf, buflen / 2);
		memcpy(rbuf, buf + buflen / 2, buflen / 2);
		return (struct pair_optional) {
			.is_pair = true,
			.a = strtoll(lbuf, NULL, 10),
			.b = strtoll(rbuf, NULL, 10),
		};
	} else {
		return (struct pair_optional) {
			.is_pair = false,
		};
	}
}

long long int calculate_stones(long long int n, size_t depth) {
	if (depth == 0) {
		return 1;
	}
	
	struct mapval mapval = get_cache(n, depth);
	if (mapval.exists) return mapval.val;
	
        struct pair_optional p = has_even_digits(n);
	long long int val;
	if (n == 0) {
		val = calculate_stones(1, depth - 1);
	} else if (p.is_pair) {
		val = calculate_stones(p.a, depth - 1) + calculate_stones(p.b, depth - 1);
	} else {
		val = calculate_stones(n * 2024, depth - 1);
	}
	
	cache(n, val, depth);
	return val;
}

struct mapval get_cache(long long int key, long long int depth) {
	struct mapval *map = cachemap[depth];

	long long int search = key % (1024 * 1024);
	while (true) {
		if (map[search].exists == false) {
			return (struct mapval) {
				.exists = false,
			};
		}

		if (map[search].key == key) {
			return map[search];
		}
		
		search++;
		search %= (1024 * 1024);
	}
}

void cache(long long int key, long long int val, long long int depth) {
	struct mapval *map = cachemap[depth];
	struct mapval m_mapval = { .exists = true, .key = key, .val = val };
	long long int search = key % (1024 * 1024);
	while (true) {
		if (map[search].exists == false) {
			map[search] = m_mapval;
			return;
		}
		search++;
		search %= (1024 * 1024);
	}
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    FILE* fPointer;
    fPointer = fopen(argv[1], "r"); 

	char input[128] = {0};
	fread(input, 1, sizeof input, fPointer);

	size_t buflen = 0;
	long long int *buf = malloc(1024);

	char *cursor = input;
	while (true) {
		if (*cursor == ' ') {
			buflen++;
		} else if (*cursor == '\n') {
			buflen++;
			break;
		} else {
			buf[buflen] *= 10;
			buf[buflen] += *cursor & 15;
		}
		cursor++;
	}

	long long int sol = 0;

	for (int i = 0; i < buflen; i++) {
		sol += calculate_stones(buf[i], 75);
	}
	
	printf("%lld\n", sol);
}
