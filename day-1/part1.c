#include <stdlib.h>
#include <stdio.h>

#include "defs.h"

int compare(const void* x, const void* y) {
    // protects against overflows. credits: claude. 
    // personally, i would've done *(long*)x - *(long*)y becuase i'm stupid lol
    return (*(long*)x > *(long*)y) - (*(long*)x < *(long*)y);
}

void solve(char input[][MAX_LINE], int lc) {
    int i;
    long n1, n2;
    long a[lc], b[lc];
    for (i = 0; i < lc; ++i) {
        if (sscanf(input[i], "%ld %ld", &n1, &n2) == 2) {
            a[i] = n1;
            b[i] = n2;
        }
    }
    
    qsort(a, lc, sizeof(long), compare);
    qsort(b, lc, sizeof(long), compare);
    
    i = 0;
    long result = 0;
    for (;i < lc; ++i) {
        result += labs(a[i] - b[i]);
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
