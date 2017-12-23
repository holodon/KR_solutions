/*
Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input
from a set of named files or, if no files are named as arguments, from the
standard input. Should the file name be printed when a matching line is found?
*/

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int mgetline(char *, int);


/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                break;
            }
    if (argc < 1) {
        printf("Usage: find [-x] [-n] pattern [file...]\n");
        return -1;
    }

    if (argc == 1)                          /* no files - read stdin */
        while (mgetline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
        }
    } else {                                /* read the supplied files */
        char *pattern = *argv;
        FILE *fp;
        while (*++argv) {
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "find: can't open file %s\n.", *argv);
                return -1;
            }
            lineno = 0;
            while (fgets(line, MAXLINE, fp) != NULL) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    printf("(%s) ", *argv);
                    if (number)
                        printf("%ld: ", lineno);
                    printf("%s", line);
                    found++;
                }
            }
        }
    }

    printf("\nTotal: %i occurrences.\n", found);
    return found;
}

/* mgetline: read a line into s, return length */
int mgetline(char s[], int lim)
{
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
