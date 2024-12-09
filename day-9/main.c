#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    FILE* fPointer;
    fPointer = fopen(argv[1], "r");

    long long sum = 0, sum2 = 0;

    fscanf(fPointer, "%s", buf);
    int buflen = strlen(buf);

    int nextid = 0;
    for (int i = 0; i < buflen; i++) {
        int l = buf[i] - '0';
        int id;
        if (i & 1) id = -1;
        else id = nextid++;
        for (int j = 0; j < l; j++) {
            map[n++] = id;
        }
    }

    for (int i = 0, j = n - 1; i <= j; i++) {
        if (map[i] >= 0) {
            sum += i * map[i];
        } else {
            while (j > i && map[j] < 0) {
                j--;
            }
            if (j <= i) break;
            sum += i * map[j];
            j--;
        }
    }

    for (int sbeg = n - 1; sbeg >= 0; ) {
        while (sbeg >= 0 && map[sbeg] < 0) {
            sbeg--;
        }
        if (sbeg < 0) break;
        int id = map[sbeg];
        int send = sbeg - 1;
        while (send >= 0 && map[send] == id) {
            send--;
        }
        int slen = sbeg - send;
        int dbeg = 0, dlen = 0;
        while (dbeg <= send) {
            while (dbeg <= send && map[dbeg] >= 0) {
                dbeg++;
            }
            if (dbeg > send) break;
            int dend = dbeg + 1;
            while (dend < n && map[dend] < 0) {
                dend++;
            }
            dlen = dend - dbeg;
            if (dlen >= slen) break;
            dbeg = dend;
            dlen = 0;
        }
        if (dlen >= slen) {
            for (int i = 0; i < slen; i++) {
                map[dbeg + i] = id;
                map[send + 1 + i] = -1;
            }
        }
        sbeg = send;
    }

    for (int i = 0; i < n; i++) {
        if (map[i] >= 0) {
            sum2 += i * map[i];
        }
    }

    printf("%lld %lld", sum, sum2);
}
