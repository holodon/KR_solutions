/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the
previous section.

Implmented as minscanf - reading one line at a time from stdin and returning
the count of succesfull matches.

WIP - now it works but processes just one line
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXLINE 100

int minscanf(char *, ...);
int mgetline(char [], int);
char line[MAXLINE];


int main(void)
{
    int day, month, year;
    char monthname[20];
    int res = 0;

    // while (mgetline(line, MAXLINE) > 0) {
    while (res != -1) {
        printf("Input: \n");
        res = minscanf(" %d/%d/%d", &day, &month, &year);
        printf("result: %d\n", res);
        if (res == 3) {
            printf("d: %d, m: %d, y: %d\n", day, month, year);
            printf("---Done\n\n");
        }
        res = scanf("%*[^\n] ");     /* advance to next line */
        // res = scanf("\n");    /* consume white space */
    }

    return 0;
}

/* minscanf: minimal scanf with variable argument list */
int minscanf(char *fmt, ...)
{
    va_list ap;                     /* points to each unnamed arg in turn */
    char *p, *sval;
    int *ival;
    unsigned *uival;
    double *dval;

    int i = 0;                      /* expression index */
    int res = 0;                    /* this will hold the result from scanf */

    /* string buffer for expressions like "%-10s" */
    #define EXPRLEN 10
    char expr[EXPRLEN];

    va_start(ap, fmt);              /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        i = 0;                      /* start over */

        if (*p == ' ') {
            scanf(" ");             /* skip whitespace */
            continue;
        }

        if (*p != '%') {            /* arbitrary character */
            expr[0] = '%';          /* build expr in format like %*[c] */
            expr[1] = '*';
            expr[2] = '[';
            expr[3] = *p;
            expr[4] = ']';
            expr[5] = '\0';
            res += scanf(expr);
            continue;
        }

        expr[i++] = '%';            /* build an expression */
        while (*(p + 1) && !isalpha(*(p + 1))) {
            if (i == EXPRLEN - 3)
                p++;                /* too long? skip to prevent overflow */
            else
                expr[i++] = *++p;
        }

        expr[i++] = *(p + 1);
        expr[i] = '\0';

        switch (*++p) {
        case 's':
            sval = va_arg(ap, char *);
            res += scanf(expr, sval);
            break;
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'c':
            ival = va_arg(ap, int *);
            res += scanf(expr, ival);
            break;
        case 'u':
            uival = va_arg(ap, unsigned *);
            res += scanf(expr, uival);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double *);
            res += scanf(expr, dval);
            break;
        default:                    /* unknown character */

            // scanf(expr);
            break;
        }
    }
    va_end(ap);                     /* clean up when done */

    return res;
}

/* mgetline: get line into s, return length */
int mgetline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}
