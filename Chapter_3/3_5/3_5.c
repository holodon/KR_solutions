/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into 
a base b character representation in the string s . In particular, 
itob(n,s,16) formats n as a hexadecimal integer in s .
*/

#include <stdio.h>
#include <string.h>
#define MAX 1000

void itob(int n, char s[], int b);
int format(int n, int b);
void reverse(char s[]);


int main(void)
{
    int n = 3234;

    char out[MAX];

    itob(n, out, 16);

    reverse(out);
    printf("%s\n", out);

    return 0;
}


void itob(int n, char s[], int b)
{
    int i = 0;

    do {
        s[i++] = format(n, b);
    } while ((n /= b) && (i < MAX - 1));
    s[i] = '\0';
}


// helper for the formatting
int format(int n, int b)
{
    n %= b;
    return (b == 16)
        ? (n > 9)
            ? (n - 10 + 'A')
            : (n + '0')
        : n + '0';
}


// reverse string s in place
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
