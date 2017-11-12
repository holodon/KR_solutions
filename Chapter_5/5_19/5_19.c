/*
Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
declarations.

- added some basic error handling
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void merror(char *err);

int tokentype;                  /* type of last token */
char token[MAXTOKEN];           /* last token string */
char name[MAXTOKEN];            /* identifier name */
char datatype[MAXTOKEN];        /* data type = char, int, etc. */
char out[1000];                 /* output string */
int emptyLine = 1;
int error = 0;
int gottoken = 0;               /* if we have token already */


/* undcl: convert word descriptions to declarations */
int main(void)
{
    printf("---undcl---\n");
    int type;
    char temp[MAXTOKEN];
    int nexttoken(void);
    int count = 0;

    while (gettoken() != EOF) {
        if ((!error) && (!emptyLine))
            strcpy(out, token);
        while ( ((type = gettoken()) != '\n') && !(error) ) {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ( ((type = nexttoken()) == PARENS) || (type == BRACKETS))
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                error = 1;
        }
        if (error) {
            error = 0;
            printf(" /!/ invalid input at %s\n", token);
        } else if (type == '\n'){
            printf("declaration %i: %s\n", ++count, out);
        }
        out[0] = '\0';
    }

    printf("\n\nDone.\n");
    return 0;
}

/* return next token */
int gettoken(void)
{
    if (gottoken) {                     /* token from the last lookup */
        gottoken = 0;
        return tokentype;
    }

    int c, getch(void);
    void ungetch(int);
    int skipspace();
    char *p = token;
    c = skipspace();
    if (c != '\n')                      /* deal with empty lines */
        emptyLine = 0;
    if (c == '(') {
        c = skipspace();                /* to deal with (   ) */
        if (c == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p = getch()) != ']'; )

            /* line break || possible SEGV */
            if ((*p == '\n') || (! *++p)) {
                merror("expected ']'");
                break;
            }
        *++p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else

    return tokentype = c;
}

#define BUFSIZE 100
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */


/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (c == EOF)
        return;

    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* get one more token (lookahead) */
int nexttoken(void)
{
    int type;
    gottoken = 1;
    return type = gettoken();
}

/* error handler */
void merror(char *err)
{
    printf(" /!/ error: %s\n", err);
    error = 1;
}

/* skip spaces, tabs and empty lines */
int skipspace()
{
    int c;
    while ((c = getch()) == ' ' || c == '\t' || ((c == '\n') && (emptyLine)) )
        ;
    if (c == '\n')          /* the end of a non-empty line */
        emptyLine = 1;      /* start the new line assuming empty */
    return c;
}
