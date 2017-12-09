/*
Exercise 5-18. Make dcl recover from input errors.

error recovery from:
    - repeated names
    - malformed input
    - empty lines
    - more spaces
    - possible SEGV when getting the brackets
also show the line numbers where errors are found
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };
void dcl(void);
void dirdcl(void);
int gettoken(void);
void merror(char *err);

int tokentype;                  /* type of last token */
char token[MAXTOKEN];           /* last token string */
char name[MAXTOKEN];            /* identifier name */
char datatype[MAXTOKEN];        /* data type = char, int, etc. */
char out[1000];                 /* output string */
int error = 0;
int emptyLine = 1;              /* 1 - empty, 0 - not empty */
int currLine = 1;               /* line counter */


/* convert declaration to words */
int main(void)
{
    printf("---dcl---\n\n");

    while (gettoken() != EOF) {
        do {
            strcpy(datatype, token);    /* 1st token on line is the datatype */
            out[0] = '\0';
            dcl();                      /* parse rest of line */
            if (tokentype != '\n') {
                merror("expected '\\n'");
            }
        } while ((tokentype != '\n') && (!error));

        if (error)
            error = 0;
        else
            printf("%s: %s %s\n", name, out, datatype);
    }

    printf("\n\nDone.\n");
    return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; )   /* count *'s */
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    if (tokentype == '(') {             /* ( dcl ) */

        dcl();

        if (tokentype != ')')
            merror("missing ')'");

    } else if (tokentype == NAME)      /* variable name */
        strcpy(name, token);

    else if (!emptyLine)
            merror("expected name or (dcl)");

    while ((type=gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* return next token */
int gettoken(void)
{
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
    int c = (bufp > 0) ? buf[--bufp] : getchar();
    if (c == '\n')
        currLine++;
    return c;
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

    if (c == '\n')
        currLine--;
}

/* error handler */
void merror(char *err)
{
    printf(" /!/ (line %i) error: %s\n", currLine, err);
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
