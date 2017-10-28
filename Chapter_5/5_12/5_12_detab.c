/*
Exercise 5-12. Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient 
(for the user) default behavior.

detab - build upon 1_20 and 5_11
*/

#include <stdio.h>
#include <stdlib.h>

int margc;
char **margv;

int startAt = -1;       // optional parameter
int tabStops = -1;      // optional parameter
int allCols = 0;        // column count row

#define MAXERRORS 50
int errors[MAXERRORS];  // this saves all wrong parameters
int currErr = -1;

int arg = 1;            // argument counter
int deftab = 8;         // default tab size

int getnewtab(void);

int main(int argc, char *argv[])
{

    // check arguments
    if (
        argc > 4 && 
        *argv[1] == '-' && 
        *(argv[1] + 1) == 'm' && 
        *argv[3] == '+' && 
        *(argv[3] + 1) == 'n' &&
        ( (startAt = atoi(argv[2])) <= 0 || (tabStops = atoi(argv[4])) <= 0 )
        )
    {
        printf("Usage: %s -m starting_at +n tab_stops [tab_stop ..]\n", 
            argv[0]);
        return 1;
    } else
        arg = 5;

    printf("startAt: %i\n", startAt);
    printf("tabStops: %i\n", tabStops);

    margc = argc;
    margv = argv;

    int c, i;
    int col = 0;                        // column count after last tab
    int currtab = 8;                    // default tab size

    while((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            col = 0;
            allCols = 0;
            arg = (tabStops == -1)? 1:5;
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
            allCols++;
            if (col == currtab) {
                currtab = getnewtab();
                col = 0;
            }
        }
    }

    if (currErr >= 0) {
        printf("\n\n\n");
        for (i = 0; i < currErr; i++)
            printf("Bad tab value: '%s'. Assuming default: '%i'.\n", 
                argv[errors[i]], deftab);
    }

    printf("\n\ndone\n");
    return 0;
}

// save all errors
void countErrors(int ar) {
    if (currErr + 1 == MAXERRORS)
        return;

    errors[++currErr] = ar;
}

// returns the next tab size
int getnewtab(void)
{
    int currtab;

    if (startAt > 0 && tabStops > 0 && allCols >= startAt)
        currtab = tabStops;
    else {
        if (arg < margc)
            if ((currtab = atoi(margv[arg])) <= 0) {
                currtab = deftab;
                countErrors(arg);
            }
    }

    arg++;

    return currtab;
}
