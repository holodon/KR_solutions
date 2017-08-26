/*
Exercise 3-4. In a two's complement number representation, our version of 
itoa does not handle the largest negative number, that is, the value of n 
equal to -(2^wordsize-1 ). Explain why not. Modify it to print that value 
correctly, regardless of the machine on which it runs.

because: -(INT_MIN) is equal to INT_MIN in two's complement
see also:
https://en.wikipedia.org/wiki/Two's_complement#Most_negative_number

implementation without 'reverse'
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void itoa(int n, char s[]);
int nsize(int n);


int main(void)
{
    char s[100];
    int n = INT_MIN;

    printf("int   : %d\n", n);

    itoa(n, s);
    printf("string: %s\n",s);

    return 0;
}


// itoa: convert n to characters in s
void itoa(int n, char s[])
{
    int i, k;
    i = 0;

    if (n < 0) {
        s[i++] = '-';
    }

    k = nsize(n) + i;

    s[k--] = '\0';

    do {
        s[k--] = abs(n % 10) + '0';
    } while (n /= 10);
}


int nsize(int n)
{
    int i = 0;
    do
        i++;
    while (n /= 10);
    return i;
}
