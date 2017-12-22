/*
Exercise 7-6. Write a program to compare two files, printing the first line
where they differ.
*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 100


int main(int argc, char *argv[])
{
    char *prog = argv[0];
    if (argc < 3) {
        printf("%s: compare two files\n", prog);
        printf("Usage:\t%s file1 file2\n", prog);
        return 1;
    }
    FILE *fpf, *fps;
    char *name_f = argv[1];
    char *name_s = argv[2];
    if ((fpf = fopen(name_f, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n",
                prog, name_f);
        return 1;
    }
    if ((fps = fopen(name_s, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n",
                prog, name_s);
        return 1;
    }

    char line_f[MAXLINE], line_s[MAXLINE];  /* line buffers */
    int line = 0;                           /* line counter */
    int res = 0;

    while ((fgets(line_f, MAXLINE, fpf) != NULL) &&
                (fgets(line_s, MAXLINE, fps) != NULL)) {
        line++;
        if (strcmp(line_f, line_s) != 0) {
            printf("first difference at line %i:\n", line);
            printf("line %i in \"%s\":\n\t%s\n", line, name_f, line_f);
            printf("line %i in \"%s\":\n\t%s\n", line, name_s, line_s);
            res = 1;
            break;
        }
    }

    if (!res)
        printf("The files \"%s\" and \"%s\" has the same content.\n",
                name_f, name_s);

    fclose(fpf);
    fclose(fps);
    return 0;
}
