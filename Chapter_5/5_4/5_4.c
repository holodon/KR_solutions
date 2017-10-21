/*
Exercise 5-4. Write the function strend(s,t) , which returns 1 if the 
string t occurs at the end of the string s , and zero otherwise.
*/

#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    char *s = "Good Morning!";
    char *t = "ning!";
    char *t1 = "boom";

    printf("s:  %s\n", s);
    printf("t:  %s\n", t);
    printf("t1: %s\n", t1);
    printf("\n");
    printf("t  at the end of s? %i\n", strend(s,t));
    printf("t1 at the end of s? %i\n", strend(s,t1));

    return 0;
}

/* strend: return 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t) {
    int i = 0,j = 0;
    while (*s) {        /* find end of s, count size */
        s++;
        i++;
    }
    while (*t) {        /* find end of t, count size */
        t++;
        j++;
    }

    if (j > i)          /* t is bigger than s */
        return 0;

    while (j >= 0) {    /* check moving backwards */
        if (*(s - j) != *(t - j))
            return 0;
        j--;
    }

    return 1;
}
