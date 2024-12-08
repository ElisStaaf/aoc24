#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "defs.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>\n", argv[0]);
        return 0;
    }

    FILE* file = fopen(argv[1], "r");
    int sum[2] = {};
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int x, y;
        if (2 != sscanf(line, "%d|%d", &x, &y)) break;
        order[x][y] = true;
    }

    while (fgets(line, sizeof(line), file)) {
        int pages[30], n = 0;
        char* t = strtok(line, ",\n");
        while (t) {
            sscanf(t, "%d", &pages[n++]);
            t = strtok(NULL, ",\n");
        }

        bool sorted = true;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (order[pages[j]][pages[i]]) {
                    int tmp = pages[i];
                    pages[i] = pages[j];
                    pages[j] = tmp;
                    sorted = false;
                }
            }
        }
        sum[!sorted] += pages[n / 2];
    }

    printf("%d %d\n", sum[0], sum[1]);
}
