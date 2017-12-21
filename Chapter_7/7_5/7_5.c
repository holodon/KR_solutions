/*
Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or
sscanf to do the input and number conversion.

Building on top of 4.3-4.6

Compile with '-lm' for the math calls.
WIP - almost ready, still not properly returning EOF
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

double last = 0;        /* last printed value */
double vars[] =         /* general purpose variables */
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int var;                /* current variable */
int where = -1;         /* where to store the res */


/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int adv = 0;

    int err= 0;

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
        case '^':
            op2 = pop();
            push(powf(pop(), op2));
            break;
        case 's':
            push(sin(pop()));
            break;
        case 'c':
            push(cos(pop()));
            break;
        case 'e':
            push(expf(pop()));
            break;
        case 'l':       /* use the last value */
            push(last);
            break;
        case 'v':       /* use a variable */
            push(vars[var]);
            break;
        case '\n':
            if (!adv) {
                double d = pop();
                last = d;
                if (where != -1) {
                    vars[where] = d;
                    where = -1;
                }
                printf("\t%.8g\n", d);
            }
            adv = 0;
            break;
        case ' ':       /* advanced commands */
            adv = 1;
            break;
        case '>':       /* skip */
            break;
        default:
            err++;
            printf("(debug) unknown int: %i\n", type);
            printf("error: unknown command %s\n", s);
            printf("use 'h' to get help\n\n");
            if (err == 10) {
                printf("\ntoo much errors - quitting...\n\n");
                return 1;
            }
            break;
        }
    }
    return 0;
}

#define MAXVAL 100          /* maximum depth of val stack */
int sp = 0;                 /* next free stack position */
double val[MAXVAL];         /* value stack */


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
void printStack();

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i;
    char c;
    scanf("%*[ ^/n]");  /* consume all white space except '\n' */
    scanf("%c", &c);
    s[0] = c;
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
    case 'l':           /* print last */
        printf("last: \t%.8g\n", last);
        return ' ';
    case '_':
        scanf("%c", &c);
        s[1] = c;
        if (isdigit(c)) {
            var = c;
            return 'v'; /* use a variable */
        }
        switch (c) {
            case 's':   /* sin */
            case 'c':   /* cos */
            case 'e':   /* exp */
            case 'l':   /* use last */
                return c;
            default:
                s[1] = '\0';
                break;
        }
        break;
    case '@':           /* store the value in a variable */
        scanf("%c", &c);
        s[1] = c;
        if (isdigit(c)) {
            where = c;
            return '>'; /* skip to next */
        }
        s[1] = '\0';
        break;
    case '.':
        break;
    case '-':           /* '-' followed by number? */
        scanf("%c", &c);
        if (!isdigit(s[1] = c)) {
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
        do {
            scanf("%c", &c);
            s[++i] = c;
        } while (isdigit(c));
    if (c == '.')           /* collect fraction part */
        do {
            scanf("%c", &c);
            s[++i] = c;
        } while (isdigit(c));
    s[i] = '\0';
    // if (c != EOF)
    //     ungetch(c);
    return NUMBER;
}

/* print the stack */
void printStack()
{
    if (sp == 0) {
        printf("Stack: empty\n");
        return;
    }
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
    printf("Supported commands:\n\n");
    printf("Arithmetic: "
        "\n\t'+', '-', '*', '/, '^', "
        "\n\t'_s' (sin), '_c' (cos), '_e' (exp)\n\n");
    printf("Advanced: \n\t'p'- print stack, "
        "\n\t's' - swap the top two in stack,"
        "\n\t'd' - duplicate stack, "
        "\n\t'c' - clear stack\n\n");
    printf("Variables: "
        "\n\t'_l' (last result), "
        "\n\t'@[0-9]' (set gen. purpose variable),"
        "\n\t'_[0-9]' (use gen. purpose variable)\n\n");
}
