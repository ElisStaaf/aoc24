#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "defs.h"

bool CheckSafeReport(int Values[], int Columns) 
{
    bool SafeReport = true;
    bool Increasing = true;  
    bool Decreasing = true;
    int Diff, AbsDiff, Column;

    for (Column = 0; Column < Columns; Column++)
    {
        Diff = Values[Column + 1] - Values[Column];
        AbsDiff = abs(Diff);

        if (AbsDiff < 1 || AbsDiff > 3)
        {
            SafeReport = false;
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
        SafeReport = false;
    }

    return SafeReport;
}

bool CheckUnsafeReport(int Values[], int cols) 
{
    int i, j;

    for (i = 0; i <= cols; i++) 
    {
        int NewValues[MAX_COLUMNS] = {0};
        int NewCols = 0;
        for (j = 0; j <= cols; j++) 
        {
            if (j != i) 
            {
                NewValues[NewCols++] = Values[j];
            }
        }

        if (CheckSafeReport(NewValues, NewCols - 1)) 
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char **argv) {
    if (argc < 1) {
        printf("Usage: %s <path/to/file.txt>", argv[0]);
        return 0;
    }

    char line[MAX_LEN];
    int Values[MAX_ROWS][MAX_COLUMNS] = {0};
    int Rows = 0;
    int ColumnsPerRow[MAX_ROWS] = {0};
    int Row;
    int SafeCount = 0;
    int Columns; 
    bool SafeReport;

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
        Columns = 0;

        while (token != NULL && Columns < MAX_COLUMNS) {
            Values[Rows][Columns] = atoi(token); 
            Columns++;
            token = strtok(NULL, " ");       
        }
        ColumnsPerRow[Rows] = Columns - 1;
        Rows++;
    }

    for (Row = 0; Row < Rows; Row++)
    {
        SafeReport = CheckSafeReport(Values[Row], ColumnsPerRow[Row]);

        if (!SafeReport)
        {
            SafeReport = CheckUnsafeReport(Values[Row], ColumnsPerRow[Row]);
        }

        if (SafeReport) 
        {
            SafeCount++;
        }
    }
    
    fclose(fPointer);

    printf("Number of safe reports are : %d\n", SafeCount);
    return 0;
}
