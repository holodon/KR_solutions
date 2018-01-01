/*
Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
operations. Compare code size and execution speed.

- Version with field operations.
- Some identifiers renamed to avoid collisions with stdio.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>


#define OPEN_MAX 20         /* max #files open at once */
#define PERMS 0666          /* RW for owner, group, others */

struct _fflags {
    unsigned _fREAD  :1;    /* file open for reading */
    unsigned _fWRITE :1;    /* file open for writing */
    unsigned _fUNBUF :1;    /* file is unbuffered */
    unsigned _fEOF   :1;    /* EOF has occurred on this file */
    unsigned _fERR   :1;    /* error occurred on this file */
};

typedef struct _iobuf {
    int cnt;                /* characters left */
    char *ptr;              /* next character position */
    char *base;             /* location of buffer */
    struct _fflags flag;    /* mode of file access */
    int fd;                 /* file descriptor */
} MFILE;

MFILE _iob[OPEN_MAX];

int _fillbuf(MFILE *);

#define mfileno(p)      ((p)->fd)

#define mgetc(p)        (--(p)->cnt >= 0 \
                            ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define mgetchar()      mgetc(mstdin)

MFILE *mfopen(char *, char *);
void error(char *, ...);
char *prog;                                 /* program name for errors */


/* play with a file using our routines */
int main(int argc, char *argv[]) {
    prog = argv[0];

    if (argc == 1) {
        printf("Usage: %s file\n", prog);
        exit(1);
    }

    int c;
    MFILE *fp;
    if ((fp = mfopen(argv[1], "r")) == NULL)
        error("can't open %s", argv[1]);

    while ((c = mgetc(fp)) != EOF)
        putchar(c);

    free(fp->base);
    close(mfileno(fp));

    return 0;
}


MFILE *mfopen(char *name, char *mode)
{
    int fd;
    MFILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag._fREAD == 0 && fp->flag._fWRITE == 0)
            break;                          /* found free slot */
    if (fp >= _iob + OPEN_MAX)              /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)                           /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flag._fREAD = 1;
        fp->flag._fWRITE = 0;
    } else {
        fp->flag._fREAD = 0;
        fp->flag._fWRITE = 1;
    }

    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(MFILE *fp)
{
    int bufsize;

    if(fp->flag._fREAD == 0 || fp->flag._fEOF == 1 || fp->flag._fERR == 1)
        return EOF;
    if (fp->flag._fUNBUF == 1)
        bufsize = 1;
    else
        bufsize = BUFSIZ;
    if (fp->base == NULL)                   /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;                     /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag._fEOF = 1;
        else
            fp->flag._fERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* error: print an error message and die */
void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s error: ", prog);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
