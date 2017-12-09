/*
Exercise 5-20. Expand dcl to handle declarations with function argument types,
qualifiers like const , and so on.

This is a solution from "The C Answer book"

gettoken.c
*/

#include <ctype.h>
#include <string.h>

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

extern int tokentype;               /* type of last token */
extern char token[];                /* last token string */
int prevtoken = NO;                 /* there is no previous token */

/* gettoken: return nest token */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
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
