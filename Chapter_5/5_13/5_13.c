/*
Exercise 5-13. Write the program tail , which prints the last n lines of its 
input. By default, n is set to 10, let us say, but it can be changed by an 
optional argument so that

tail -n

prints the last n lines. The program should behave rationally no matter how 
unreasonable the input or the value of n. Write the program so it makes the 
best use of available storage; lines should be stored as in the sorting 
program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>         // for atoi()

#define MAXLINES 5000       // max #lines to be sorted
#define MAXLEN 1000         // max length of any input line
#define MAXSIZE 10000       // max size of the buffer

char *lineptr[MAXLINES];    // pointers to text lines

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int from, int to);



int main(int argc, char *argv[])
{
    int n = 10;                     // default value of n

    // check arguments
    if ( 
        (argc > 3) || (argc < 3 && argc > 1) ||
        (argc == 3) &&
            (
                (*argv[1] != '-') || 
                (*(argv[1] + 1) != 'n') || 
                ((n = atoi(argv[2])) <= 0)
            )
        )
    {
        printf("Usage: %s -n lines\n", argv[0]);
        return 1;
    }

    char storage[MAXSIZE];          // big enough array

    int nlines;                     // number of input lines read
    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {

        if (n > nlines)
            n = nlines;

        writelines(lineptr, (nlines - n), nlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }


    return 0;
}

int mgetline(char *s, int lim);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char storage[])
{

    int len, nlines, currpos, start;
    nlines = currpos = start = 0;

    while ( (len = mgetline(&storage[currpos], MAXLEN)) > 0 ) {
        currpos += len;
        if (nlines >= maxlines || currpos >= MAXSIZE)
            return -1;
        else {
            /* delete newline */
            storage[currpos - 1] = '\0';
            lineptr[nlines++] = &storage[start];
            start = currpos;
        }
    }

    return nlines;
}

/* writelines: write a range from the lines */
void writelines(char *lineptr[], int from, int to)
{
    int i;
    for (i = from; i < to; i++)
        printf("%s\n", lineptr[i]);
}

/* getline: get line into s, return length */
/* pointer version */
int mgetline(char *s, int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (*s = getchar()) != EOF && *s != '\n') {
        s++;
        i++;
    }
    if (*s == '\n') {
        s++;
        i++;
    }
    *s = '\0';

    return i;
}
