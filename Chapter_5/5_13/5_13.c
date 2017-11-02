/*
Exercise 5-13. Write the program tail , which prints the last n lines of its 
input. By default, n is set to 10, let us say, but it can be changed by an 
optional argument so that

tail -n

prints the last n lines. The program should behave rationally no matter how 
unreasonable the input or the value of n. Write the program so it makes the 
best use of available storage; lines should be stored as in the sorting 
program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>     // for atoi()

int n = 10;             // default n

int main(int argc, char *argv[])
{
    // check arguments
    if ( 
        (argc > 3) || (argc < 3 && argc > 1) ||
        (argc == 3) &&
            (
                (*argv[1] != '-') || 
                (*(argv[1] + 1) != 'n') || 
                (n = atoi(argv[2])) <= 0 
            )
        )
    {
        printf("Usage: %s -n lines\n", argv[0]);
        return 1;
    }


    return 0;
}
