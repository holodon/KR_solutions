/*
Exercise 5-7. Rewrite readlines to store lines in an array supplied by main , 
rather than calling alloc to maintain storage. How much faster is the program?
*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000               /* max #lines to be sorted */
#define MAXLEN 1000                 /* max length of any input line */
#define MAXSIZE 10000               /* max size of the buffer */

char *lineptr[MAXLINES];            /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
    char storage[MAXSIZE];          /* big enough array */

    int nlines;                     /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)              /* do nothing if array contains */
        return;                     /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

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
