#ifndef __LIB1__
#define __LIB1__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_LINES 1500

int read_input(char *filename, char lines[][MAX_LINE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    int line_count = 0;
    char *line_result;
	while (!feof(file) && !ferror(file)) {
        // Clear the buffer before reading
        memset(lines[line_count], 0, MAX_LINE);
        
        // Attempt to read a line
        line_result = fgets(lines[line_count], MAX_LINE, file);
        
        // Break if we've reached EOF
        if (line_result == NULL) {
            break;
        }

        // Remove newline character if present
        size_t len = strlen(lines[line_count]);
        if (len > 0 && lines[line_count][len-1] == '\n') {
            lines[line_count][len-1] = '\0';
        }
        
        line_count++;
    }
    if (ferror(file)) {
        printf("Error reading file: %s\n", filename);
        fclose(file);
        exit(1);
    }
    fclose(file);
    return line_count;
}

#endif
