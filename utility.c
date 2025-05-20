#include "utility.h"

void stringToUpper(char* string)
{
    while(*string != '\0')
    {
        *string = (char)toupper((unsigned char)*string);
        string++;
    }
}