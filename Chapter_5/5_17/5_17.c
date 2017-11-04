/*
Exercise 5-17. Add a field-searching capability, so sorting may bee done on 
fields within lines, each field sorted according to an independent set of 
options. (The index for this book was sorted with -df for the index category 
and -n for the page numbers.)
*/

#include <stdio.h>
#include <string.h>                 /* for strcmp */
#include <stdlib.h>                 /* for atof */
#include <strings.h>                /* for strcasecmp */
#include <ctype.h>                  /* for isalnum */

#define MAXLINES 5000               /* max #lines to be sorted */
#define MAXLEN 1000                 /* max length of any input line */
#define MAXSIZE 10000               /* max size of the buffer */

char *lineptr[MAXLINES];            /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, 
    int (*comp)(void *, void *));
int numcmp(char *, char *);
int mycmp(char *, char *);
void showUsage(char *prname);

int numeric = 0;                    /* 1 if numeric sort */
int reverse = 1;                    /* -r flag reverse sorting [-1,+1] */
int ignorecase = 0;                 /* 1 if ignoring case */
int dirorder = 0;                   /* 1 if sort by directory order */
int fieldStart = 0, fieldStop = 0;  /* the field to be compared */

/* sort input lines */
int main(int argc, char *argv[])
{
    char storage[MAXSIZE];          /* big enough array */
    int nlines;                     /* number of input lines read */

    /* check arguments, set flags */
    char *prname = argv[0];
    int c;

    int error = 0;

    while( --argc > 0 && (((c = (*++argv)[0]) == '-') || (c == '+')) ) {
        if (c == '-' && !isdigit( *(argv[0] + 1) ))
            while(c = *++argv[0])
                switch(c)
                {
                    case 'd':
                        dirorder = 1;
                        break;
                    case 'f':
                        ignorecase = 1;
                        break;
                    case 'r':
                        reverse = -1;
                        break;
                    case 'n':
                        numeric = 1;
                        break;
                    default:
                        printf("%s: illegal option %c\n", prname, c);
                        error = 1;
                        break;
                }
        else if (c == '-')
            fieldStop = atoi(argv[0] + 1);
        else if ( (fieldStart = atoi(argv[0] + 1)) < 0 )
            showUsage(prname);
    }

    if ( argc || error || (fieldStart > fieldStop) ) {
        showUsage(prname);
    }

    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        mqsort((void**) lineptr, 0, nlines-1, 
            (int (*)(void*,void*))(
                mycmp
                ));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }

    return 0;
}

void showUsage(char *prname)
{
    printf("Usage: %s [-nrfd] [+fieldStart] [-fieldStop]\n", prname);
    exit(1);
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
        if ( ( (*comp)(v[i], v[left])*reverse ) < 0)
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

/* mycmp: compare with directory order (skip all except alnum and ' ' */
int mycmp(char *s1, char *s2)
{
    /* just as 5_16 if numeric or no fields set */
    if (numeric)
        return numcmp(s1, s2);

    if (fieldStop == 0) {
        if (dirorder) {
            while(!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
                s1++;
            while(!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
                s2++;
        }
        if (ignorecase)
            return strcasecmp(s1, s2);

        return strcmp(s1, s2);
    }

    /* the additional 5_17 logic */
    int i, j, endpos;
    char a = 0, b = 0;

    if ( (endpos = strlen(s1)) > (i = strlen(s2)) )
        endpos = i;

    i = j = fieldStart;
    do {
        if (dirorder) {
            while(  i < endpos && 
                    !isalnum(s1[i]) && 
                    s1[i] != ' ' && s1[i] != '\0' )
                i++;
            while(  j < endpos && 
                    !isalnum(s2[j]) && 
                    s2[j] != ' ' && s2[j] != '\0' )
                j++;
        }
        if ( (i < endpos) && (j < endpos) ) {
            a = ignorecase? tolower(s1[i]) : s1[i];
            i++;
            b = ignorecase? tolower(s2[j]) : s2[j];
            j++;

            if (a == b && a == '\0')
                return 0;
        }
    } while ( (a == b) && (i < endpos) && (j < endpos) );

    return (a - b);
}