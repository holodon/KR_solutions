/*
Exercise 7-8. Write a program to print a set of files, starting each new one on
a new page, with a title and a running page count for each file.
*/

#include <stdio.h>
#define MAXLINE 1000                        /* max line length */
#define PGLINES 5                           /* max lines on a page */

void printhdr(char *, int);


/* f(ormatted)cat - print files on pages with headers */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: %s file [file..]\n", argv[0]);
        return 1;
    }

    int lc = 0;                             /* line counter */
    int pgc = 0;                            /* page counter */
    char line[MAXLINE];                     /* line buffer */
    FILE *fp;

    while (*++argv) {
        if ((fp = fopen(*argv, "r")) == NULL) {
            fprintf(stderr, "fcat: can't open file %s\n.", *argv);
            return -1;
        }
        pgc = 1;
        printhdr(*argv, pgc);
        lc = 0;
        while (fgets(line, MAXLINE, fp) != NULL) {
            if (lc == PGLINES) {
                pgc++;
                printhdr(*argv, pgc);
                lc = 0;
            }
            lc++;
            printf("%s", line);
        }
        while (lc++ < PGLINES)              /* fill the rest with \n's */
            printf("\n");
    }

    return 0;
}

/* print a page header */
void printhdr(char *name, int page)
{
    printf("\n\n\n");
    printf("--- page %i | %s\n\n", page, name);
}
