#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "uthash.h"

typedef struct entry {
    long key;
    long value;
    UT_hash_handle hh;
} entry;

entry *map = NULL;

void add_entry(long key) {
    entry *s;
    HASH_FIND_PTR(map, &key, s);
    if (NULL == s) {
        s = (entry*)malloc(sizeof(*s));
        s->key = key;
        HASH_ADD_PTR(map, key, s);
        s->value = 1l;
        return;
    }
    s->value++;
}

long find_entry(long key) {
    entry* e;
    HASH_FIND_PTR(map, &key, e);
    if (NULL == e) {
        return 0l;
    }
    return e->value;
}

void solve(char input[][MAX_LINE], int lc) {
    long n1, n2;
    int i = 0;
    for (i = 0; i < lc; ++i) {
        if (sscanf(input[i], "%ld %ld", &n1, &n2) == 2) {
            add_entry(n2);
            printf("Incremented count for %ld to %ld\n", n2, find_entry(n2));
        }
    }
    
    long result = 0;
    for(i=0; i < lc; ++i) {
        if (sscanf(input[i], "%ld %ld", &n1, &n2) == 2) {
            result += (n1 * find_entry(n1));
        }
    }
    
    printf("Result: %ld\n", result);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s </path/to/input/file.txt>\n", argv[0]);
        exit(1);
    }
    char input[MAX_LINES][MAX_LINE];
    int lc = read_input(argv[1], input);
    solve(input, lc);
    return 0;
}
