/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the
previous section.

- The gcc warning about scanf(expr) can be ignored, because the 'expr' string is
not a random one, nor it contains uncontrolled or dangerous expression
(see l.64-70).
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int minscanf(char *, ...);


int main(void)
{
    int day, month, year;
    int res = 0, ln = 0;

    while (res != EOF) {
        ln++;
        res = minscanf(" %d/%d/%d", &day, &month, &year);
        printf("\nLine: %i\t", ln);
        printf("result: %d\n", res);
        if (res == 3) {
            printf("Full match!\t");
            printf("d: %d, m: %d, y: %d\n", day, month, year);
        } else
            printf("no (full) match\n");
        printf("---Done\n");
                                    /* advance to next line/EOF */
        res = scanf("%*[^\n]%*[\n]");
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

        int i = 0;                  /* expression index */
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
