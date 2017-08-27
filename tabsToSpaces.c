/*
Exercise 1-20. Write a program detab that replaces tabs in the 
input with the proper number of blanks to space to the next 
tab stop. Assume a fixed set of tab stops, say every n columns.
Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>
//#define n 8   // works too but we prefer variable

int main(void)
{
    int c;
    int col = 0;
    int n = 4;

    while((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            col = 0;
        } else if (c == '\t') {
            for (int i = 0; i < (n - col); i++) {
                putchar(' ');
                //putchar('_'); // for testing/ better visibility
            }
            col = 0;
        } else {
            putchar(c);
            col++;
            if (col == n)
                col = 0;
        }
    }
    return 0;
}
