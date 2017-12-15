/*
Exercise 6-6. Implement a simple version of the #define processor (i.e., no
arguments) suitable for use with C programs, based on the routines of this
section. You may also find getch and ungetch helpful.

WIP
- #define's in comments and strings count too
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {                              /* table entry: */
    struct nlist *next;                     /* next entry in chain */
    char *name;                             /* defined name */
    char *defn;                             /* replacement text */
};

/* for testing with collisions */
//#define HASHSIZE 1
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];     /* pointer table */

int undef(char *);
void printtable();
unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
char *mstrdup(char *);
void panic(const char *);
void freemem();

#define MAXWORD 100
int getword(char *, int, int);
void ungets(char *);

#define GETWORD 0
#define GETNAME 1
#define GETDEFN 2
#define ERR -404


/* a #define processor */
int main(void)
{
    int i;

    /* insert all */
    // for (i = 0; i < TESTS; i++)

    printf("%i",EOF);

    char word[MAXWORD];
    int res, count = 0;
    char name[MAXWORD];
    while (getword(word, MAXWORD, GETWORD) != EOF) {
        if (strcmp(word, "#define") == 0) {
            count++;
            if (
                    (res = getword(word, MAXWORD, GETNAME)) != ERR &&
                    res != EOF
                ) {
                strcpy(name, word);
                if (
                        (res = getword(word, MAXWORD, GETDEFN)) != ERR &&
                        res != EOF
                    )
                    if (!install(name, word))
                        panic("install");
            }
        }
        printf("%s", word);
    }
    printf("\n\n\"#define\" count: %i\n", count);
    printtable();

    /* free memory claimed by malloc */
    freemem();

    return 0;
}

/* remove entry from the lookup table
    return 1 if succesfull */
int undef(char *name)
{
    struct nlist *np;
    struct nlist *last = NULL;
    unsigned hashval = hash(name);
    for (np = hashtab[hashval]; np != NULL; last = np, np = np->next)
        if (strcmp(name, np->name) == 0) {  /* found */
            if (last)                       /* in linked list */
                last->next = np->next;
            else                            /* first entry on the row */
                hashtab[hashval] = NULL;
            free((void *) np->name);
            free((void *) np->defn);
            free((void *) np);
            return 1;
        }
    return 0;                               /* not found */
}

/* lookup and print all */
void printtable()
{
    printf("\nthe current hashtable: \n");

    int i;
    struct nlist *np;
    for (i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL) {
            printf("row %3i:", i);
            for (np = hashtab[i]; np != NULL; np = np->next)
                    printf("\t%10s-> %s\n", np->name, np->defn);
        }
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {      /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mstrdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else                                  /* already there */
    free((void *) np->defn);                /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;                      /* found */
    return NULL;                            /* not found */
}

/* mstrdup: make a duplicate of s */
char *mstrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);     /* +1 for '\0' */

    if (p == NULL)
        panic("mstrdup");

    strcpy(p, s);

    return p;
}

/* panic: exit forcefully after memory error */
void panic(const char *msg)
{
    printf("MEMORY ERROR\n");
    printf("function: %s\n", msg);
    exit(1);
}

/* clear memory */
void freemem()
{
    int i;
    struct nlist *np, *tmp;
    for (i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL) {
            np = hashtab[i];
            while(np) {
                tmp = np;
                np = np->next;
                free((void *) tmp->name);
                free((void *) tmp->defn);
                free((void *) tmp);
            }
        }
}

/* getword: get next word or character from input
    mode: GETWORD, GETDEFN, GETNAME
    return ERR if error */
int getword(char *word, int lim, int mode)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    if (mode == GETWORD)
        while (isspace(c = getch()))            /* print whitespace */
            putchar(c);
    else
        while ((c = getch()) == ' ')            /* print whitespace */
            putchar(c);

    if (mode == GETDEFN) {                  /* get #define definition */
        if (c == '"') {                     /* string */
            while ( ((c= getch()) != '"') && (c != EOF))
            if (c == '\n') {                /* malformed string */
                                            /* maybe return error? */
                putchar(c);
                break;
            } else
                *w++ = c;
            *w = '\0';
            return word[0];
        }
        while (c != EOF) {                  /* everything else */
            if (c == '\n') {
                putchar(c);
                break;
            } else
                *w++ = c;
            c = getch();
        }
    } else if (mode == GETNAME) {           /* get #define name */
        if (!isalpha(c))
            return ERR;
        while (isalpha(c) && c != EOF) {
            *w++ = c;
            c = getch();
        }
        if (c != ' ') {                     /* malformed name */
            *w = '\0';
            if (c != EOF)
                printf("%s", w);
            return ERR;
        }
    }

    /* print comments and quotes */
    if (c == '/') {
        putchar(c);
        if ( (c = getch()) == '/') {        /* single line comment */
            putchar(c);
            while ( ((c = getch()) != '\n') && (c != EOF) )
                putchar(c);
        } else if (c == '*') {              /* multiline comment */
            putchar(c);
            int done = 0;
            while (!done) {
                while ((c = getch()) != '*') {
                    if (c == EOF) {
                        *w = '\0';
                        ungetch(c);
                        return word[0];
                    }
                    putchar(c);
                }
                putchar(c);
                /* "/* ... *" until now */
                if ((c = getch()) == '/') {
                    done = 1;
                }
            }
        }
    }
    if (c == '"') {                         /* print quotes */
        while ( ((c= getch()) != '"') && (c != EOF) )
            putchar(c);
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
    else
        putchar(c);

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* pushback whole string */
void ungets(char *s)
{
    int len = strlen(s);
    if (bufp + len >= BUFSIZE)
        printf("buffer is almost/ full\n");
    else while (len > 0)
        ungetch(s[--len]);
}
