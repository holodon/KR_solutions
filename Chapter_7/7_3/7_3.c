/*
Exercise 7-3. Revise minprintf to handle more of the other facilities of
printf .
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *, ...);


int main(int argc, char *argv[])
{
    minprintf("This has to %.12s:\n\
                \tsome decimal number: %5d,\n\
                \tan octal: %-5o,\n\
                \ta hexadecimal: %X,\n\
                \tunsigned decimal: %u,\n\
                \tsome char: %c,\n\
                \ta double: %f,\n\
                \tanother double (with exp): %e,\n\
                \tone more double: %g,\n\
                \ta pointer: %p,\n\
                \tsomething unknown: %123k,\n\
                \tsomething long and malformed: %12.3.45678912_34567890i,\n\
                \tand a simple %%.\n",
                 "pretty printtt", (int) 81, (int) 81, (int) 81, (unsigned) 81,
                 (char) 81, (double) 81, (double) 81, (double) 81, (void *) 81);

    return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;                     /* points to each unnamed arg in turn */
    char *p, *sval, c;
    int ival, i;
    unsigned uival;
    double dval;
    void *ptr;

    /* string buffer for expressions like "%-10s" */
    #define EXPRLEN 10
    char expr[EXPRLEN];

    va_start(ap, fmt);              /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        /* "%%" */
        if (*(p + 1) && (*(p + 1) == '%')) {
            putchar('%');
            p++;
            continue;
        }

        /* build an expression (if any) */
        i = 0;
        expr[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1))) {
            if (i == EXPRLEN - 3)
                p++;                /* skip to prevent overflow */
            else
                expr[i++] = *++p;
        }

        expr[i++] = *(p + 1);
        expr[i] = '\0';

        switch (*++p) {
        case 's':
            sval = va_arg(ap, char *);
            printf(expr, sval);
            break;
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'X':
            ival = va_arg(ap, int);
            printf(expr, ival);
            break;
        case 'u':
            uival = va_arg(ap, unsigned);
            printf(expr, uival);
            break;
        case 'c':
            c = va_arg(ap, int);
            printf(expr, c);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            printf(expr, dval);
            break;
        case 'p':
            ptr = va_arg(ap, void*);
            printf(expr, ptr);
            break;
        default:                    /* unknown character */
            putchar('?');
            putchar(*p);
            break;
        }
    }
    va_end(ap);                     /* clean up when done */
}
