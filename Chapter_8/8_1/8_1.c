/*
Exercise 8-1. Rewrite the program cat from Chapter 7 using read , write , open ,
and close instead of their standard library equivalents. Perform experiments to
determine the relative speeds of the two versions.

This is the new version with system calls.

Can be tested with the provided big txt file like this:
    $ time ./cat_sys 56215-0.txt > /dev/null
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

#include <unistd.h>                         /* instead of K&R's "syscalls.h" */

void filecopy(int, int);
void error(char *fmt, ...);
char *prog;                                 /* program name for errors */

/* cat: concatenate files (using system calls) */
int main(int argc, char *argv[])
{
    int fd;
    prog = argv[0];

    if (argc == 1 )                         /* no args; copy standard input */
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                error("%s: can't open %s", prog, *argv);
            } else {
                filecopy(fd, 1);
                close(fd);
            }

    exit(0);
}

/* filecopy: copy file ifd to file ofd using system calls */
void filecopy(int ifd, int ofd)
{
    char buf[BUFSIZ];
    int n;
    while ((n = read(ifd, buf, BUFSIZ)) > 0)
        if (write(ofd, buf, n) != n)
            error("write error");
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
