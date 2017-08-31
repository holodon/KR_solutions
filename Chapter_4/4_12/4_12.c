/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive routine.

supporting the largest negative numbers
*/

#include <stdio.h>
#include <limits.h>     /* for INT_MIN */
#include <stdlib.h>     /* for abs() */

void itoa(int n);


int main(void)
{
    int n = INT_MIN;

    printf("int   : %d\n", n);

    printf("string: ");
    itoa(n);
    printf("\n");

    return 0;
}


// itoa: convert int n to characters
void itoa(int n)
{
    static int sign;
    if (!sign && n < 0) {
        sign = 1;
        putchar('-');
    }

    if (n / 10)
        itoa( n / 10);

    putchar(abs(n % 10) + '0');
}
