/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the
previous section.

- The gcc warning about line 71 can be ignored, because the 'expr' string is
not a random one, nor it contains uncontrolled or dangerous expression
(see l.64-70).

WIP
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int minscanf(char *, ...);


int main(void)
{
    int day, month, year;
    char monthname[20];
    int res = 0, line = 0;

    while (res != EOF) {
        line++;
        res = minscanf(" %d/%d/%d", &day, &month, &year);
        printf("Line: %i\t", line);
        printf("result: %d\n", res);
        if (res == 3) {
            printf("Full match!\t");
            printf("d: %d, m: %d, y: %d\n", day, month, year);
        } else
            printf("no (full) match\n");
        printf("---Done\n\n");
        res = scanf("%*[^\n] ");     /* advance to next line/EOF */
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

        i = 0;                      /* start over */
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
        default:                    /* unknown character - ignoring */
            break;
        }
    }
    va_end(ap);                     /* clean up when done */

    return res;
}
