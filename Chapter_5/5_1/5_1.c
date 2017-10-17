/*
Exercise 5-1. As written, getint treats a + or - not followed by a digit as 
a valid representation of zero. Fix it to push such a character back on the 
input.
*/

#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int main(void) {
    const int SIZE = 10;
    int n, p, array[SIZE], getint(int *);

    /* print the result */
    for (n = 0; n < SIZE && (p = getint(&array[n])) != EOF; n++)
        if (p != 0) 
            printf("%i\n", array[n]);
        else
            printf("non-digit\n");
    
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        /* assuming there is nothing else to be done with the rest of the
        input (with the non-digits), then ungetch is wrong here and leads 
        to loop with the next getch */
        //ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();                /* get one more character */
        /* +/- followed by non-digit:
        I would just skip both, but now to comply with the assignment: */
        if (!isdigit(c)) {          
            ungetch(c);
            return 0;
        }
    }
    /* build the int */
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    /* the last c is non-digit - push it back */
    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];                  /* buffer for ungetch */
int bufp = 0;                       /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) 
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
