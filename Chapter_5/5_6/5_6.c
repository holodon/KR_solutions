/*
Exercise 5-6. Rewrite appropriate programs from earlier chapters and
exercises with pointers instead of array indexing. Good possibilities include
getline (Chapters 1 and 4), atoi , itoa , and their variants (Chapters 2, 3,
and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'                   /* signal that a number was found */

int mgetline(char *s, int lim);
int matoi(char *s);
int matoi2(char *s);
void mitoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int getop(char *s);


int main(void)
{
    /* getline */
    const int LIMIT = 20;
    char sgetline[LIMIT];

    printf("\n===============\n");
    printf("getline (waiting for input):\n");
    printf("\tgot %i characters\n", mgetline(sgetline, LIMIT));
    printf("\tgot this: %s\n", sgetline);

    /* atoi */
    char *satoi = "325abc";

    printf("\n===============\n");
    printf("atoi:\n");
    printf("\tfound '%i' in '%s'\n", matoi(satoi), satoi);

    /* atoi version 2 */
    char *satoi2 = "   -325abc";

    printf("\n===============\n");
    printf("atoi version 2:\n");
    printf("\tfound '%i' in '%s'\n", matoi2(satoi2), satoi2);

    /* itoa */
    int iitoa = 12345;
    char sitoa[20];

    printf("\n===============\n");
    printf("itoa:\n");
    mitoa(iitoa, sitoa);
    printf("\tfound '%s' in '%i'\n", sitoa, iitoa);

    /* strindex */
    char *sstr = "Good Morning!";
    char *tstr = "ning";

    printf("\n===============\n");
    printf("strindex:\n");
    printf("\tfound '%s' at position %i in '%s'\n", tstr,
        strindex(sstr, tstr), sstr);

    /* getop */
    int type;
    char s[100];

    printf("\n===============\n");
    printf("getop (waiting for input):\n");
    while ((type = getop(s)) != EOF)
        if (type == NUMBER)
            printf("\tnumber\n");
        else
            printf("\t%c\n", type);

    /* end */
    printf("\n\nDone.\n");

    return 0;
}

/* getline: get line into s, return length */
/* pointer version */
int mgetline(char *s, int lim)
{
    int i;
    i = 0;
    while (--lim > 0 && (*s = getchar()) != EOF && *s != '\n') {
        s++;
        i++;
    }
    if (*s == '\n') {
        s++;
        i++;
    }
    *s = '\0';

    return i;
}

/* atoi: convert s to integer */
/* pointer version */
int matoi(char *s)
{
    int n = 0;
    for ( ; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');

    return n;
}

/* atoi: convert s to integer; version 2 */
/* pointer version */
int matoi2(char *s)
{
    int n, sign;
    while (isspace(*s++)) {             /* skip white space */
        ;
    }

    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')         /* skip sign */
        s++;

    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');

    return sign * n;
}

/* itoa: convert n to characters in s */
/* pointer version */
void mitoa(int n, char *s)
{
    char *ss = s;
    int sign;
    if ((sign = n) < 0)                 /* record sign */
        n = -n;                         /* make n positive */

    do {                                /* generate digits in reverse order */
        *ss++ = n % 10 + '0';           /* get next digit */
    } while ((n /= 10) > 0);            /* delete it */

    if (sign < 0)
        *ss++ = '-';
    *ss = '\0';
    reverse(s);
}

/* reverse: reverse string s in place */
/* pointer version */
void reverse(char *s)
{
    int c;
    char *ss, *ts;                      /* start/end */
    ss = ts = s;

    while (*ts)
        ts++;
    ts--;                               /* '\0' stays where it is */

    for ( ; ss < ts; ss++, ts--) {
        c = *ss;
        *ss = *ts;
        *ts = c;
    }
}

/* strindex: return index of t in s, -1 if none */
/* pointer version */
int strindex(char *s, char *t)
{
    char *ss, *ts;
    int i = 0;
    for (; *s; s++, i++) {
        ss = s; ts = t;
        for ( ; *ts && *ss == *ts; ts++, ss++)
            ;
        if (i > 0 && *ts == '\0')
            return i;
    }

    return -1;
}

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
/* pointer version */
int getop(char *s)
{
    int c;
    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';
    if (!isdigit(c) && c != '.')    /* not a number */
        return c;

    if (isdigit(c))                 /* collect integer part */
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')                   /* collect fraction part */
    while (isdigit(*++s = c = getch()))
        ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
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
