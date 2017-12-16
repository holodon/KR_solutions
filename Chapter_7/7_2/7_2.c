/*
Exercise 7-2. Write a program that will print arbitrary input in a sensible
way. As a minimum, it should print non-graphic characters in octal or
hexadecimal according to local custom, and break long text lines.

- To be safe/portable, this programm treats everything non-ascii as non-graphic
    character.
- For simplicity we assume the input is in Windows-1252 encoding
    (see the "test" file)
*/

#include <stdio.h>

/* max line length */
#define MAXLINE 80


/* pretty-print */
int main(void)
{
    int c;
    int pos = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            pos = 0;
            putchar(c);
        } else if ((c > 31) && (c < 127)) { /* printable ascii */
            pos++;
            putchar(c);
            if (pos == MAXLINE) {
                pos = 0;
                putchar('\n');
            }
        } else {                            /* non-graphic character */
            pos += 2;
            if (pos == MAXLINE) {
                pos = 0;
                printf("%X\n", c);
            } else if (pos > MAXLINE) {
                pos = 2;
                printf("\n%X", c);
            } else {
                printf("%X", c);
            }
        }
    }

    putchar('\n');
    return 0;
}
