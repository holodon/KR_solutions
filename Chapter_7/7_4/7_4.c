/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the
previous section.

Implmented as minsscanf - reading one line at a time from stdin and returning
the count of succesfull matches.

WIP
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int minsscanf(char *, ...);
int mgetline(char [], int lim);

#define MAXLINE 100
char line[MAXLINE];


int main(void)
{
    int day, month, year;
    char monthname[20];

    int l = 0;                      /* line counter */

    while (mgetline(line, sizeof(line)) > 0) {
        l++;
        printf("--->line %d:  ", l);
        printf("%s\n", line);
        printf("result: %d\n", minsscanf("%d/%d/%d", &day, &month, &year));
        printf("<---\n\n");
    }

    return 0;
}

/* minprintf: minimal printf with variable argument list */
int minsscanf(char *fmt, ...)
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
        if (*p != '%') {
            expr[i++] = *p;
            continue;
        }

        expr[i++] = '%';
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
            res += sscanf(line, expr, sval);
            break;
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
        case 'c':
            ival = va_arg(ap, int *);
            res += sscanf(line, expr, ival);
            break;
        case 'u':
            uival = va_arg(ap, unsigned *);
            res += sscanf(line, expr, uival);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double *);
            res += sscanf(line, expr, dval);
            break;
        default:                    /* unknown character */
            sscanf(line, expr);
            break;
        }
        i = 0;                      /* start over */
    }
    va_end(ap);                     /* clean up when done */

    return res;
}

/* getline: read a line into s, return length */
int mgetline(char s[], int lim)
{
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
