#ifndef __DEFS__
#define __DEFS__

#include <stdbool.h>
#include <stddef.h>

#define MIB (1024 * 1024)

struct lld_slice {
	long long int *buf;
	size_t buflen;
};

struct pair_optional {
	bool is_pair;
	long long int a;
	long long int b;
};

struct mapval {
	bool exists;
	long long int key;
	long long int val;
};

struct mapval cachemap[100][MIB] = {0};

#endif
