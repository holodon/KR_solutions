/*
Exercise 6-1. Our version of getword does not properly handle underscores,
string constants, comments, or preprocessor control lines. Write a better
version.

Support for '_', '#', comments, quotes and backslash
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
    char *word;
    int count;
} keytab[] = {
    {"#define", 0},             /* testing #define #define */
    {"__mtest", 0},             /* testing #define #define */
    {"_mtest", 0},              /* testing #define #define */
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"if", 0},
    {"int", 0},
    {"main", 0},
    {"return", 0},
    {"struct", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

#define ADVANCEDPARSING 1       /* set this to 0 to compare the test cases */

/* test strings to test this program against its own source:
break break break break break
break break break break break
break break break break break
break break break break break
 */
 // char char char char char
 // char char char char char
 // char char char char char
char test[] = "const const \" const const const const";
int _mtest = 0;
void __mtest(void)
{
    _mtest++;
    _mtest--;
    return;
}
/* test cases above _mtest _mtest */


#define NKEYS (sizeof keytab / sizeof(keytab[0]))
#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main(void)
{
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        if ( (isalpha(word[0])) || (word[0] == '_') || (word[0] == '#') )
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
    return 0;
}
/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))            /* skip whitespace */
        ;

    /* corner cases enabled: skip comments and quotes */
    if (ADVANCEDPARSING) {
        if (c == '/') {
            if ( (c = getch()) == '/')          /* single line comment */
                while ( ((c = getch()) != '\n') && (c != EOF) )
                    ;
            else if (c == '*') {                /* multiline comment */
                int done = 0;
                while (!done) {
                    while ((c = getch()) != '*')
                        if (c == EOF) {
                            *w = '\0';
                            ungetch(c);
                            return word[0];
                        }
                    /* "/* ... *" until now */
                    if ((c = getch()) == '/')
                        done = 1;
                }
            }
        }
        if (c == '"') {                         /* quotes */
            while ( ((c= getch()) != '"') && (c != EOF) )
                ;
        }
    }

    /* "normal" word */
    if ( (isalpha(c) || (c == '#') || (c == '_')) &&
            (--lim > 0) ) {
        *w++ = c;                           /* get first character */
        while ( ((isalnum(c = getch())) || (c == '_')) &&
                    (--lim > 0) )
            *w++ = c;                       /* build the whole word */
    }

    if (c == EOF)
        return c;                           /* EOF */

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)             /* get a (possibly pushed-back) character */
{
    int c;

    /* ignore one (special) character after a backslash */
    /* somewhat -ugly- but it works for the current goal */
    if ((c = (bufp > 0) ? buf[--bufp] : getchar()) == '\\') {
        if ( ((c = (bufp > 0) ? buf[--bufp] : getchar()) == EOF) ||
                (isalnum(c)) )
            return c;
        else
            return (bufp > 0) ? buf[--bufp] : getchar();
    }
    return c;
}

void ungetch(int c)         /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
