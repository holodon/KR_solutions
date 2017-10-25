/*
Exercise 5-10. Write the program expr , which evaluates a reverse Polish 
expression from the command line, where each operator or operand is a 
separate argument. For example,

expr 2 3 4 + "*"
evaluates 2 * (3+4).

Note: take care to call it with "*" instead of just '*' because the terminal
interprets * as a command
*/

#include <stdio.h>
#include <ctype.h>                      /* for isdigit() */
#include <stdlib.h>                     /* for atof() */
#define MAXOP                           /* max size of operand or operator */
#define NUMBER '0'                      /* signal that a number was found */
#define WRONGNUM '1'                    /* neither operator nor number */

int getop (char *);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    /* check arguments */
    if (argc < 2) {
        printf("Usage: %s arguments\n", argv[0]);
        return 1;
    }

    int type, ar = 1;
    double op2;

    while (ar < argc) {
        type = getop(argv[ar]);
        switch (type) {
            case NUMBER:
                push(atof(argv[ar]));
                break;

            case '+':
                push(pop() + pop());
                break;

            case '*':
                push(pop() * pop());
                break;

            case '-':
                op2 = pop();
                push(pop() - op2);
                break;

            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;

            default:
                printf("error: unknown command %s\n", argv[ar]);
                break;
        }
        ar++;
    }

    /* print the res */
    printf("\t%.8g\n", pop());

    return 0;
}

/* getop: parse s and return operand, NUMBER or WRONGNUM */
int getop(char *s)
{
    char *tmp = s;
    while (*tmp == ' ' || *tmp == '\t')     /* skip white space */
        tmp++;

    if (!isdigit(*tmp) && *tmp != '.') 
        return *tmp;                        /* not a number */

    /* check if valid number */
    int point = 0;
    while (*tmp) {
        if (*tmp == '.')
            if (point)
                return WRONGNUM;
            else
                point = 1;
        else
            if (!isdigit(*tmp))
                return WRONGNUM;
        tmp++;
    }

    return NUMBER;
}

#define MAXVAL 100                      /* maximum stack size */
int sp = 0;                             /* stack position */
double val[MAXVAL];                     /* stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
