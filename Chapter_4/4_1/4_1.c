/*
Exercise 4-1. Write the function strindex(s,t) which returns the position of 
the rightmost occurrence of t in s , or -1 if there is none.
*/

#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]);


int main(void)
{
    char s[] = "would if would else would be wouold not";
    //char s[] = "here is nothing";
    //          0        9          20
    char t[] = "ould";

    int res = strindex(s, t);
    printf("%d\n", res);
    if (res >= 0)
        printf("%c\n", s[res]);
    return 0;
}


int strindex(char s[], char t[])
{
    int i, j, k;
    int slen = strlen(s) - 1;
    int tlen = strlen(t) - 1;

    for (i = slen; i >= 0; i--) {
        for (j = i, k = tlen; k >= 0 && s[j] == t[k]; j--, k--)
            ;
        if (k == -1)
            return i - tlen;
    }
    return -1;
}