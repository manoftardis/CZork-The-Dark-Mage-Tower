#ifndef UTILITY_H
#define UTILITY_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void stringToUpper(char* string)
{
    while(*string != '\0')
    {
        *string = toupper((unsigned char)*string);
        string++;
    }
}

#endif