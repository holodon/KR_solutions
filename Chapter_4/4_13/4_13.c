/*
Exercise 4-13. Write a recursive version of the function reverse(s) , which 
reverses the string s in place.
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void reverse2(char s[], int i, int j);


int main(void)
{
    char s[] = "!ynnuf skool sihT";
    printf("%s\n\n", s);

    reverse(s);
    printf("%s\n", s);

    char t[] = "!ynnuf skool sihT";
    reverse2(t, 0, strlen(t) - 1);
    printf("%s\n", t);

    return 0;
}


/* reverse: reverse string s in place */
void reverse(char s[])
{
    static int c, i, j;

    if (j == 0)
        j = strlen(s) - 1;

    if (i == j)
        return;

    c = s[i];
    s[i] = s[j];
    s[j] = c;
    i++;
    j--;

    reverse(s);
}


/* reverse2: reverse string s in place w/o static vars */
void reverse2(char s[], int i, int j)
{
    if (i == j)
        return;

    int c = s[i];
    s[i] = s[j];
    s[j] = c;
    reverse2(s, ++i, --j);
}
