/*
Exercise 5-14. Modify the sort program to handle a -r flag, which indicates 
sorting in reverse (decreasing) order. Be sure that -r works with -n .
*/

#include <stdio.h>
#include <string.h>                 /* for strcmp */
#include <stdlib.h>                 /* for atof */

#define MAXLINES 5000               /* max #lines to be sorted */
#define MAXLEN 1000                 /* max length of any input line */
#define MAXSIZE 10000               /* max size of the buffer */

char *lineptr[MAXLINES];            /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, 
    int (*comp)(void *, void *));
int numcmp(char *, char *);

int reverse = 1;                    /* -r flag reverse sorting [-1,+1] */

/* sort input lines */
int main(int argc, char *argv[])
{
    char storage[MAXSIZE];          /* big enough array */
    int nlines;                     /* number of input lines read */
    int numeric = 0;                /* 1 if numeric sort */

    int error = 0;

    // check arguments, set flags
    if (argc == 2) {
        if ( strcmp(argv[1], "-n") == 0 )
            numeric = 1;
        else if ( strcmp(argv[1], "-r") == 0 )
            reverse = -1;
        else if ( strcmp(argv[1], "-rn") == 0 ) {
            reverse = -1;
            numeric = 1;
        }
        else if ( strcmp(argv[1], "-nr") == 0 ) {
            reverse = -1;
            numeric = 1;
        }
        else
            error = 1;
    } else if (argc > 2)
        error = 1;

    if (error) {
        printf("Usage: %s [-nr]\n", argv[0]);
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        mqsort((void**) lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }

    return 0;
}

int mgetline(char *s, int lim);

/* readlines: read input lines to storage */
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}


/* mqsort: sort v[left]...v[right] into increasing order */
void mqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right)              /* do nothing if array contains */
        return;                     /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ( ((*comp)(v[i], v[left])*reverse) < 0)
            swap(v, ++last, i);
        swap(v, left, last);
        mqsort(v, left, last-1, comp);
        mqsort(v, last+1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[],int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}
