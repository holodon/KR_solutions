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
    int lc_f, lc_s;                         /* line counter */
    lc_f = lc_s = 0;
    int res = 0;
    int eoff = 0;                           /* EOF watcher */

    do {
        if (fgets(line_f, MAXLINE, fpf) == NULL)
            eoff = 1;
        else
            lc_f++;

        if (fgets(line_s, MAXLINE, fps) == NULL)
            eoff = 1;
        else
            lc_s++;

        if (strcmp(line_f, line_s) != 0) {
            res = 1;
            break;
        }
    } while (!eoff);

    if (lc_f != lc_s)
        printf("The file \"%s\" is %s than \"%s\".\n",
                name_f, (lc_f > lc_s)? "bigger":"smaller", name_s);
    else if (res) {
        printf("first difference at line %i:\n", lc_f);
        printf("line %i in \"%s\":\n\t%s\n", lc_f, name_f, line_f);
        printf("line %i in \"%s\":\n\t%s\n", lc_f, name_s, line_s);
    } else
        printf("The files \"%s\" and \"%s\" has the same content.\n",
                name_f, name_s);

    fclose(fpf);
    fclose(fps);
    return 0;
}
