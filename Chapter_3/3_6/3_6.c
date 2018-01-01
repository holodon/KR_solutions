/*
Exercise 3-6. Write a version of itoa that accepts three arguments instead of
two. The third argument is a minimum field width; the converted number must
be padded with blanks on the left if necessary to make it wide enough.

implementation without 'reverse'
*/

#include <stdio.h>
#include <stdlib.h>

void itoa2(int n, char s[], int l);
int nsize(int n);


int main(void)
{
    char s[100];
    int n = -3267;
    int l = 10;

    printf("ruler  : ");
    int i;
    for (i = 0; i < l; i++)
        printf(".");
    printf("\n");

    itoa2(n, s, l);
    printf("string : %s\n",s);

    return 0;
}


void itoa2(int n, char s[], int l)
{
    int k, minus;
    minus = 0;

    k = nsize(n);

    if (n < 0) {
        minus = 1;
        k++;
    }

    if (k < l)
        k = l;

    s[k--] = '\0';

    do {
        s[k--] = abs(n % 10) + '0';
    } while (n /= 10);

    if (minus)
        s[k--] = '-';

    while(k >= 0)
        s[k--] = ' ';
}


int nsize(int n)
{
    int i = 0;
    do
        i++;
    while (n /= 10);
    return i;
}
