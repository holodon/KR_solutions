/*
Exercise 7-1. Write a program that converts upper case to lower or lower case
to upper, depending on the name it is invoked with, as found in argv[0] .
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* lower: convert input to lower case*/
int main(int argc, char *argv[])
{
    int to_lower = (strstr(argv[0], "tolower") != NULL) ? 1:0;

    int c;
    while ((c = getchar()) != EOF)
        if (to_lower)
            putchar(tolower(c));
        else
            putchar(toupper(c));
    return 0;
}
