#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "defs.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    FILE* fPointer;
    fPointer = fopen(argv[1], "r");

    int sum = 0;

    while (1 == fscanf(fPointer, "%s", &M(n, 0))) n++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M(i, j) != '.') {
                pair_t* p = &pairs[(int)M(i, j)];
                assert(p->n < COUNT(p->pairs));
                p->pairs[p->n][0] = i;
                p->pairs[p->n][1] = j;
                p->n++;
            }
        }
    }

    for (int u = 0; u < COUNT(pairs); u++) {
        pair_t* p = &pairs[u];
        for (int v = 0; v < p->n; v++) {
            for (int w = v + 1; w < p->n; w++) {
                int* pv = p->pairs[v];
                int* pw = p->pairs[w];
                int d[2] = { pw[0] - pv[0], pw[1] - pv[1] };
                sum += sweep(pw, d, 2);
                d[0] *= -1;
                d[1] *= -1;
                sum += sweep(pv, d, 2);
            }
        }
    }

    printf("%d\n", sum);
}
