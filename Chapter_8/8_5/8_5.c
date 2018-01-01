/*
Exercise 8-5. Modify the fsize program to print the other information contained
in the inode entry.
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_PATH 1024

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));


/* print file name */
int main(int argc, char **argv)
{
    printf("\n");
    printf(" mode    inode        size  name\n");
    printf("--------------------------------\n");

    if (argc == 1)                          /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);

    printf("\n");
    return 0;
}

/* fsize: print the name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if (S_ISDIR(stbuf.st_mode))
        dirwalk(name, fsize);
    printf("%6o  %5ld %10ld %s\n", stbuf.st_mode, stbuf.st_ino,
        stbuf.st_size, name);
}


/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0))
            continue;                       /* skip self and parent */
        if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
