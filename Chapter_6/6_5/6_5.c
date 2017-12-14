/*
Exercise 6-5. Write a function undef that will remove a name and definition
from the table maintained by lookup and install .

WIP - not yet working
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {                              /* table entry: */
    struct nlist *next;                     /* next entry in chain */
    char *name;                             /* defined name */
    char *defn;                             /* replacement text */
};

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

const struct test {
    char *name;
    char *defn;
} mtest[] = {
    {"one", "-1-"},
    {"two", "-2-"},
    {"three", "-3-"}
};
#define TESTS (sizeof mtest / sizeof(mtest[0]))


/* hash lookup table */
int main(void)
{
    int i;

    /* insert all */
    for (i = 0; i < TESTS; i++)
        if (!install(mtest[i].name, mtest[i].defn))
            panic("install");

    printtable();

    printf("\n");

    /* remove an entry */
    if (!undef(mtest[0].name))
        printf("entry not found");

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
    for (np = hashtab[hash(name)]; np != NULL; last = np, np = np->next)
        if (strcmp(name, np->name) == 0) {  /* found */
            printf("removing entry: \"%s\"\n", name);
            if (last) {
                last->next = np->next;
            }
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
        if (hashtab[i] != NULL)
            for (np = hashtab[i]; np != NULL; np = np->next)
                    printf(" %-10s-> %s\n", np->name, np->defn);
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
    for (i = 0; i < HASHSIZE; i++)
        if (hashtab[i] != NULL) {
            free(hashtab[i]->name);
            free(hashtab[i]->defn);
            free(hashtab[i]);
        }
}
