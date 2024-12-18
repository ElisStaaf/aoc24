#ifndef __DEFS__
#define __DEFS__

#include <ctype.h>

#define DATA_SIZE 100000

int FindNumber(int index, char* data, int* newIndex) {
    int number = 0;

    if (isdigit(data[index])) 
    {
        number = data[index] - '0';
        *newIndex = index + 1; 
    }

    if (isdigit(data[index]) && isdigit(data[index + 1])) 
    {
        number = 10 * (data[index] - '0') + (data[index + 1] - '0');
        *newIndex = index + 2; 
    } 

    if (isdigit(data[index]) && isdigit(data[index + 1]) && isdigit(data[index + 2])) 
    {
        number = 100 * (data[index] - '0') + 10 * (data[index + 1] - '0') + (data[index + 2] - '0');
        *newIndex = index + 3; 
    }

    return number;
}

#endif
