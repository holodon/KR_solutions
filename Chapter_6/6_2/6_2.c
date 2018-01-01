/*
Exercise 6-2. Write a program that reads a C program and prints in alphabetical
order each group of variable names that are identical in the first 6 characters,
but different somewhere thereafter. Don't count words within strings and
comments. Make 6 a parameter that can be set from the command line.

Implemented as simple as possible: generate the tree with groups, instead of
single words, then print it showing the count of the words in each group.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
    char *group;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100

int getword(char *word, int lim, int advparsing);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct tnode *talloc(void);
char *mstrdup(char *s);
void freemem(struct tnode *p);

size_t readChars = 6;

/* find groups with similar words */
int main(int argc, char* argv[])
{
    /* read/set "read first x chars" parameter */
    if (argc > 1)
        if ( (readChars = atoi(argv[1])) <= 0 )
            readChars = 6;

    /* build the tree */
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD, 1) != EOF)
        if (isalpha(word[0]) && strlen(word) >= readChars)
            root = addtree(root, word);

    /* print the tree */
    treeprint(root);

    /* not (yet) discussed in K&R but I added it here anyway,
    to release the memory claimed with "malloc" */
    freemem(root);

    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {                /* a new word has arrived */
        p = talloc();               /* make a new node
                                        (start a new group) */
        p->group = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->group, readChars)) == 0)
        p->count++;                 /* repeated word */
    else if (cond < 0)              /* less than into left subtree */
        p->left = addtree(p->left, w);
    else                            /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("group: %s | words: %4d\n", p->group, p->count);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    struct tnode* p = (struct tnode *) malloc(sizeof(struct tnode));
    if (p == NULL)
        printf("MEMORY ERROR\n");
    return p;
}

/* mstrdup: make a duplicate of s */
char *mstrdup(char *s)
{
    char *p;
    p = (char *) calloc(1, readChars + 1);           /* +1 for '\0' */

    if (p != NULL) {
        strncpy(p, s, readChars);
        /* strncpy does not add '\0' at the end */
        s[readChars] = '\0';
    }
    else
        printf("MEMORY ERROR\n");

    return p;
}

/* freemem: frees memory recursively */
void freemem(struct tnode *p)
{
    if (p != NULL) {
        if (p->left != NULL) {
            freemem(p->left);
        }
        if (p->right != NULL) {
            freemem(p->right);
        }
        free(p->group);
        free(p);
    }
}

/* getword: get next word or character from input */
int getword(char *word, int lim, int advparsing)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))                /* skip whitespace */
        ;

    /* corner cases enabled: skip comments and quotes */
    if (advparsing) {
        if (c == '/') {
            if ( (c = getch()) == '/')          /* single line comment */
                while ( ((c = getch()) != '\n') && (c != EOF) )
                    ;
            else if (c == '*') {                /* multiline comment */
                int done = 0;
                while (!done) {
                    while ((c = getch()) != '*')
                        if (c == EOF) {
                            *w = '\0';
                            ungetch(c);
                            return word[0];
                        }
                    /* "/* ... *" until now */
                    if ((c = getch()) == '/')
                        done = 1;
                }
            }
        }
        if (c == '"') {                         /* quotes */
            while ( ((c= getch()) != '"') && (c != EOF) )
                ;
        }
    }

    /* "normal" word */
    if ( (isalpha(c) || (c == '#') || (c == '_')) &&
            (--lim > 0) ) {
        *w++ = c;                               /* get first character */
        while ( ((isalnum(c = getch())) || (c == '_')) &&
                    (--lim > 0) )
            *w++ = c;                           /* build the whole word */
    }

    if (c == EOF)
        return c;                               /* EOF */

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    int c;
    /* ignore one (special) character after a backslash */
    if ((c = (bufp > 0) ? buf[--bufp] : getchar()) == '\\') {
        if ( ((c = (bufp > 0) ? buf[--bufp] : getchar()) == EOF) ||
                (isalnum(c)) )
            return c;
        else
            return (bufp > 0) ? buf[--bufp] : getchar();
    }
    return c;
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
