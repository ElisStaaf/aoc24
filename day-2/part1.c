#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "defs.h"

int main(int argc, char **argv) {
    if (argc < 1) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    char line[MAX_LEN];
    int Values[MAX_ROWS][MAX_COLUMNS] = {0};
    int rows = 0;
    int cols_per_row[MAX_ROWS] = {0};
    int Row;
    int Column;
    bool Safe;
    bool Increasing;
    bool Decreasing;
    int SafeCount = 0;
    int Diff;
    int AbsDiff;
    int cols; 

    FILE * fPointer;
    fPointer = fopen(argv[1], "r");

    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    while (fgets(line, sizeof(line), fPointer) != NULL) 
    {
        char *token = strtok(line, " "); 
        cols = 0;

        while (token != NULL && cols < MAX_COLUMNS) {
            Values[rows][cols] = atoi(token); 
            cols++;
            token = strtok(NULL, " ");       
        }
        cols_per_row[rows] = cols - 1;
        rows++;
    }

    for (Row = 0; Row < rows; Row++)
    {
        Safe = true;
        Increasing = true;  
        Decreasing = true;

        for (Column = 0; Column < cols_per_row[Row]; Column++)
        {
            Diff = Values[Row][Column + 1] - Values[Row][Column];
            AbsDiff = abs(Diff);
            
            if (AbsDiff < 1 || AbsDiff > 3)
            {
                Safe = false;
                break;
            }

            if (Diff > 0) 
            {
                Decreasing = false;
            }
            else if (Diff < 0)
            {
                Increasing = false;
            } 
        }

        if (!(Increasing || Decreasing)) 
        {
            Safe = false;
        }

        if (Safe) 
        {
            SafeCount++;
        }
    }
    fclose(fPointer);

    printf("Number of safe rows are : %d\n", SafeCount);
    return 0;
}
