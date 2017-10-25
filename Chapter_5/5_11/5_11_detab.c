/*
Exercise 5-11. Modify the program entab and detab (written as exercises in 
Chapter 1) to accept a list of tab stops as arguments. Use the default tab 
settings if there are no arguments.

detab - build upon 1_20
*/

#include <stdio.h>
#include <stdlib.h>

int margc;
char **margv;
int arg = 1;            // argument counter
int deftab = 8;         // default tab size

int getnewtab(void);

int main(int argc, char *argv[])
{
    margc = argc;
    margv = argv;

    int c, i;
    int col = 0;                        // column counter
    int currtab = 8;                    // default tab size

    while((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            col = 0;
            arg = 1;
        } else if (c == '\t') {
            for (i = 0; i < (currtab - col); i++) {
                putchar(' ');
                //putchar('_');           // for testing
            }
            currtab = getnewtab();
            col = 0;
        } else {
            putchar(c);
            col++;
            if (col == currtab) {
                currtab = getnewtab();
                col = 0;
            }
        }
    }

    return 0;
}

// returns the next tab size
int getnewtab(void)
{
    int currtab;
    if ((arg < margc) && ((currtab = atoi(margv[arg])) > 0) )
        ;
    else
        currtab = deftab;
    arg++;

    return currtab;
}
