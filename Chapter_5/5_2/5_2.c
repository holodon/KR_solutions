/*
Exercise 5-2. Write getfloat, the floating-point analog of getint. What type 
does getfloat return as its function value?

build on top of 5.1
*/

#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int main(void) {
    const int SIZE = 10;
    float array[SIZE];
    int n, p, getfloat(float *);

    /* print the result */
    for (n = 0; n < SIZE && (p = getfloat(&array[n])) != EOF; n++)
        if (p != 0) 
            printf("%f\n", array[n]);
        else
            printf("non-digit\n");
    return 0;
}

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
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
    /* build the int part */
    int i;
    for (i = 0; isdigit(c); c = getch())
        i = 10 * i + (c - '0');
    *pn = (float) i;

    /* build the float part */
    if (c == '.') {
        c = getch();                /* get one more */
        if (!isdigit(c))
            ungetch(c);
        else {
            int p = 1;
            int afterP = 0;
            for (afterP = 0; isdigit(c); c = getch()) {
                afterP = 10 * afterP + (c - '0');
                p *= 10;
            }
            *pn += (float) afterP / p;
        }
    }
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
