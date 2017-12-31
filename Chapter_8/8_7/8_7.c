/*
Exercise 8-7. malloc accepts a size request without checking its plausibility;
free believes that the block it is asked to free contains a valid size field.
Improve these routines so they make more pains with error checking.

- More comments - K&R malloc it is a great piece of software,
    after understanding it.
- Modified mfree to make sure the pointer does not get reused

- WIP - still not ready
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef long Align;             /* for alignment to long boundary */
union header {                  /* block header */
    struct {
        union header *ptr;      /* next block if on free list */
        size_t size;            /* size of this block */
                                /*      including the Header itself */
                                /*      measured in count of Header chunks */
                                /*      not less than NALLOC Header's */
    } s;
    Align x;                    /* force alignment of blocks */
};
typedef union header Header;

static Header *morecore(size_t);
void *mmalloc(size_t);
void mfree(void *);
void visualize(const char*);

size_t totmem = 0;              /* total memory requested trough sbrk */

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */
// #define NALLOC 1024             /* minimum chunks to request */
#define NALLOC 1                /* for testing */


int main(void)
{
    char *pc;
    long *pd;
    int dlen = 10;
    int ddlen = 50;

    visualize("start");

    /* claim and then free a string */
    if ((pc = (char *) mmalloc(dlen * sizeof(char))) == NULL)
        return -1;
    visualize("string alloc");
    mfree(pc);
    visualize("free(string)");

    /* claim and then free a char */
    if ((pc = (char *) mmalloc(sizeof(char))) == NULL)
        return -1;
    visualize("char alloc");
    mfree(pc);
    visualize("free(char)");


    /* claim and then free a doubles */
    if ((pd = (long *) mmalloc(ddlen * sizeof(long))) == NULL)
        return -1;
    visualize("long alloc");

    mfree(pd);
    visualize("free(double)");

    printf("--- Memory claimed  : %ld chunks\n", totmem);
    printf("    Free memory now : %ld chunks\n", freep->s.size);
    if (freep->s.size == totmem)
        printf("    No memory leaks detected.\n");
    else
        printf("    (!) Leaking memory: %ld chunks.\n",
                    (totmem - freep->s.size));
    printf("// Done.\n");

    return 0;
}


/* visualize: print the circular tree (educational purpose) */
void visualize(const char* msg)
{
    Header *tmp;
    tmp = freep;                            /* find the start of the list */

    printf("--- Free list after \"%s\":\n", msg);

    if (freep == NULL) {                    /* does not exist */
        printf("\tList does not exist\n\n");
        return;
    }

    if  (tmp == tmp->s.ptr) {               /* self-pointing list = empty */
        printf("\tList is empty\n\n");
        return;
    }

    printf("  ");
    while (tmp->s.ptr != freep) {           /* traverse the list */
        printf("ptr: %p size: %lu -->  ", (void *) tmp, tmp->s.ptr->s.size);
        tmp = tmp->s.ptr;
    }
    printf("end\n");
    printf("\tTotal memory claimed: %lu chunks\n\n", totmem);
}


/* mmalloc: general-purpose storage allocator */
void *mmalloc(size_t nbytes)
{
    Header *p, *prevp;
    size_t nunits;

    /* smallest count of Header-sized memory chunks */
    /*  (+1 additional chunk for the Header itself) needed to hold nbytes */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {          /* no free list yet */
        /* set the list to point to itself */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    /* traverse the circular list */
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {

        if (p->s.size >= nunits) {          /* big enough */
            if (p->s.size == nunits)        /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {                          /* allocate tail end */
                /* adjust the size */
                p->s.size -= nunits;
                /* find the address to return */
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }

        /* back where we started and nothing found - we need to allocate */
        if (p == freep)                     /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL;                /* none left */
    }
}


/* morecore: ask system for more memory */
/*      nu: count of Header-chunks needed */
static Header *morecore(size_t nu)
{
    char *cp;
    Header *up;

    /* get at least NALLOC Header-chunks from the OS */
    if (nu < NALLOC)
        nu = NALLOC;

    cp = (char *) sbrk(nu * sizeof(Header));

    if (cp == (char *) -1)                  /* no space at all */
        return NULL;

    printf("... (sbrk) claimed %ld chunks\n", nu);
    totmem += nu;                           /* keep track of allocated memory */

    up = (Header *) cp;
    up->s.size = nu;

    /* add the free space to the circular list */
    mfree((void *)(up+1));

    return freep;
}


/* mfree: put block ap in free list */
void mfree(void *ap)
{
    if (ap == NULL)
        return;

    Header *bp, *p;
    bp = (Header *)ap - 1;                  /* point to block header */

    /* look where to insert the free space */

    /* (bp > p && bp < p->s.ptr)    => between two nodes */
    /* (p > p->s.ptr)               => this is the end of the list */
    /* (p == p->p.str)              => list is one element only */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            /* freed block at start or end of arena */
            break;

    if (bp + bp->s.size == p->s.ptr) {      /* join to upper nbr */
    /* the new block fits perfect up to the upper neighbor */

        /* merging up: adjust the size */
        bp->s.size += p->s.ptr->s.size;
        /* merging up: point to the second next */
        bp->s.ptr = p->s.ptr->s.ptr;

    } else
        /* set the upper pointer */
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {              /* join to lower nbr */
    /* the new block fits perfect on top of the lower neighbor */

        /* merging below: adjust the size */
        p->s.size += bp->s.size;
        /* merging below: point to the next */
        p->s.ptr = bp->s.ptr;

    } else
        /* set the lower pointer */
        p->s.ptr = bp;

    /* reset the start of the free list */
    freep = p;

    /* the free space is only marked as free, but 'ap' still points to it */
    /* to avoid reusing this address and corrupt our structure set it to NULL */
    ap = NULL;
}
