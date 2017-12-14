/*
Exercise 6-3. Write a cross-referencer that prints a list of all words in a
document, and for each word, a list of the line numbers on which it occurs.
Remove noise words like ``the,'' ``and,'' and so on.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
    struct lnode *lines;
};

struct lnode {
    int line;
    struct lnode *next;
};

#define MAXWORD 100

/* keep track of line numbers */
int currline = 1;

int getword(char *word, int lim, int advparsing);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void llprint(struct lnode *l);
struct tnode *talloc(void);
struct lnode *lalloc(void);
char *mstrdup(char *s);
void freemem(struct tnode *p);
void freell(struct lnode *l);
void panic(const char *msg);
int noiseword(const char *word);


/* cross-referencer */
int main(void)
{
    /* build the tree */
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD, 0) != EOF)
        if (isalpha(word[0]) && (!noiseword(word)))
            root = addtree(root, word);

    /* print the tree */
    printf("\n");
    treeprint(root);
    printf("\n");

    /* not (yet) discussed in K&R but I added it here anyway,
    to release the memory claimed with "malloc" */
    freemem(root);

    return 0;
}

/* notnoise: disgard "noise" words
    return 1 if the word is in the list */
int noiseword(const char *word)
{
    /* the top 27 "noise" words in english - found it somewhere online */
    const char *noisew[] = {
        "the",
        "and",
        "a",
        "to",
        "of",
        "in",
        "i",
        "is",
        "that",
        "it",
        "on",
        "you",
        "this",
        "for",
        "but",
        "with",
        "are",
        "have",
        "be",
        "at",
        "or",
        "as",
        "was",
        "so",
        "if",
        "out",
        "not"
    };

    /* binary search */
    int end = sizeof(noisew) / sizeof(noisew[0]) - 1;
    int begin = 0;
    int mid;
    int cond = 0;
    while (begin <= end) {
        mid = (begin + end) /2;
        if ((cond = strcmp(word, noisew[mid])) == 0)
            return 1;
        else if (cond < 0)
            end = mid - 1;
        else
            begin = mid + 1;
    }

    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {                /* a new word has arrived */
        p = talloc();               /* make a new node */
        p->word = mstrdup(w);
        p->left = p->right = NULL;
        p->lines = lalloc();
        (p->lines)->line = currline;
        (p->lines)->next = NULL;

    } else if ((cond = strcmp(w, p->word)) == 0) {
        /* repeated word - insert in a linked list */

        struct lnode *l = p->lines;
        struct lnode *tmp;

        if (currline != l->line) {
            tmp = lalloc();
            tmp->next = l->next;
            l->next = tmp;

            if (currline > l->line) {
                tmp->line = l->line;
                l->line = currline;
            } else
                tmp->line = currline;
        }


    } else if (cond < 0) {          /* less than into left subtree */
        p->left = addtree(p->left, w);

    } else {                        /* greater than into right subtree */
        p->right = addtree(p->right, w);
    }

    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);

        printf(" %-20s\t", p->word);
        struct lnode *l = p->lines;
        llprint(l);

        /* this removes the last comma on the line
        (maybe not working in all terminals) */
        printf("\b\b ");

        printf("\n");

        treeprint(p->right);
    }
}

/* print a linked list backwards; free memory */
void llprint(struct lnode *l)
{
    if (l->next)
        llprint(l->next);

    printf("%i, ", l->line);
    free(l);
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    struct tnode* p = (struct tnode *) malloc(sizeof(struct tnode));
    if (p == NULL)
        panic("talloc");

    return p;
}

/* lalloc: make a lnode */
struct lnode *lalloc(void)
{
    struct lnode* p = (struct lnode *) malloc(sizeof(struct lnode));
    if (p == NULL)
        panic("lalloc");

    p->next = NULL;

    return p;
}

/* mstrdup: make a duplicate of s */
char *mstrdup(char *s)
{
    char *p;
    p = (char *) calloc(1, strlen(s) + 1);           /* +1 for '\0' */

    if (p == NULL)
        panic("mstrdup");

    strcpy(p, s);

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
        free(p->word);
        free(p);
    }
}

/* panic: exit forcefully after memory error */
void panic(const char *msg)
{
    printf("MEMORY ERROR\n");
    printf("function: %s\n", msg);
    exit(1);
}

/* getword: get next word or character from input */
int getword(char *word, int lim, int advparsing)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))                /* skip whitespace */
        if (c == '\n')
            currline++;

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
        ungetch(c);
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
