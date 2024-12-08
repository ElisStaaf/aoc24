#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "defs.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path/to/file.txt>\n", argv[0]);
        return 0;
    }
    char character;
    char data[DATA_SIZE];
    int i = 0;
    int index;
    int sum = 0;

    FILE * fPointer;
    fPointer = fopen(argv[1], "r");

    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    while ((character = getc(fPointer)) != EOF) {
        if (character != '\n' && character != ' ') {
            data[i] = character;
            i++;
        }
    }

    bool disableInstructions = false;

    for (index = 0; index < i; index++)
    {
        int number1 = 0;
        int number2 = 0;

        if (data[index] == 'd' && data[index + 1] == 'o' && data[index + 2] == 'n' &&
            data[index + 3] == '\'' && data[index + 4] == 't' && data[index + 5] == '('
            && data[index + 6] == ')')
        {
            disableInstructions = true;
            continue;
        }
        else if (data[index] == 'd' && data[index + 1] == 'o' && data[index + 2] == '(' &&
                data[index + 3] == ')')
        {
            disableInstructions = false;
        }

        if (!disableInstructions && data[index] == 'm' && data[index + 1] == 'u' && 
            data[index + 2] == 'l' && data[index + 3] == '(')
        {
            index = index + 4;
            int newIndex;
            number1 = FindNumber(index, data, &newIndex);
            index = newIndex;

            if (data[index] == ',')
            {
                index++;
                number2 = FindNumber(index, data, &newIndex);
                index = newIndex;
            }
            else
            {
                continue;
            }

            if (data[index] == ')')
            {
                sum += number1 * number2;
            }
        }
    }

    fclose(fPointer);

    printf("The total sum is: %d\n", sum);
    
    return 0;
}
