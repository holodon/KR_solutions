/*
Exercise 5-3. Write a pointer version of the function strcat that we showed 
in Chapter 2: strcat(s,t) copies the string t to the end of s .
*/

#include <stdio.h>

void mstrcat(char *s, char *t);

int main(void)
{
    char t[] = " two";
    char s[20];
    s[0] = 'o';
    s[1] = 'n';
    s[2] = 'e';
    s[3] = '\0';

    mstrcat(&s[0], &t[0]);
    printf("%s\n",s);

    return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void mstrcat(char *s, char *t)
{
    while (*s)          /* find end of s */
        s++;
    while (*s++ = *t++) /* copy t */
        ;
}
