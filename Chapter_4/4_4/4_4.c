/*
Exercise 4-4. Add the commands to print the top elements of the stack without 
popping, to duplicate it, and to swap the top two elements. Add a command to 
clear the stack.

Building on top of 4.3
*/

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <math.h>       /* for fmod() */
#define MAXOP 100       /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */


int getop(char []);
void push(double);
double pop(void);
void printUsage();

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int adv = 0;

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                if (!adv)
                    printf("\t%.8g\n", pop());
                adv = 0;
                break;
            case ' ':       // advanced commands
                adv = 1;
                break;
            default:
                printf("error: unknown command %s\n", s);
                printf("use 'h' to get help\n");
                break;
        }
    }
    return 0;
}

#define MAXVAL 100      /* maximum depth of val stack */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */


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


#include <ctype.h>
int getch(void);
void ungetch(int);

void printStack();

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;

    switch (c) {
        case 'h':           /* help */
            printUsage();
            return ' ';
        case 'p':           /* print */
            printStack();
            return ' ';
        case 'd':           /* duplicate */
            if (((sp - 1) * 2 + 1) >= MAXVAL) {
                printf("Unable to duplicate - possible stack overflow\n");
                return ' ';
            }
            int st = sp;
            while ( i < st ) {
                val[st + i] = val [i];
                i++;
            }
            sp += i;
            printStack();
            return ' ';
        case 's':           /* swap */
            if (sp < 2) {
                printf("Too few elements\n");
                return ' ';
            }
            i = val[sp - 1];
            val[sp - 1] = val[sp - 2];
            val[sp - 2] = i;
            printStack();
            return ' ';
        case 'c':           /* clear */
            sp = 0;
            printStack();
            return ' ';
        case '.':
            break;
        case '-':           /* '-' followed by number? */
            if (!isdigit(s[1] = c = getch())) {
                ungetch(c);
                s[1] = '\0';
                return '-';
            }
            else
                i = 1;
            break;
        default:
            if (!isdigit(c))
                return c;
            break;
    }

    if (isdigit(c))         /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')           /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}


/* print the stack */
void printStack()
{
    int i = 0;
    printf("Stack: ");
    while (i < sp)
        printf("%f ", val[i++]);
    printf("\n");    
}


/* print usage */
void printUsage()
{
    printf("\n");
    printf("Supported commands:\n");
    printf("Arithmetic: '+', '-', '*', '/'\n");
    printf("Advanced  : 'p'- print stack, 's' - swap the top two in stack,\n"
        " 'd' - duplicate stack, 'c' - clear stack\n");
    printf("\n");
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
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
