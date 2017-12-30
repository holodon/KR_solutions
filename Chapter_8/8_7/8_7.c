/*
Exercise 8-7. malloc accepts a size request without checking its plausibility;
free believes that the block it is asked to free contains a valid size field.
Improve these routines so they make more pains with error checking.

WIP - just got the K&R version working, but this is still not the excersice
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef long Align;             /* for alignment to long boundary */
union header {                  /* block header */
    struct {
        union header *ptr;      /* next block if on free list */
        unsigned size;          /* size of this block */
    } s;
    Align x;                    /* force alignment of blocks */
};
typedef union header Header;

static Header *morecore(size_t);
void *mmalloc(size_t);
void mfree(void *);

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */
#define NALLOC 1024                         /* minimum #units to request */


int main(void)
{
    char *mstring = "Hello world!\n";
    int len = strlen(mstring) + 1;
    char *pc, *tmp;
    int *pi;

    if ((pc = (char *) mmalloc(len * sizeof(char))) == NULL)
        return -1;

    if ((pi = (int *) mmalloc(sizeof(int))) == NULL)
        return -1;

    tmp = pc;
    while (*mstring)
        *tmp++ = *mstring++;
    *tmp = '\0';
    printf("%s", pc);

    *pi = 755;
    printf("%i\n", *pi);

    printf("%p\n", *freep);
    mfree(pc);
    printf("%p\n", *freep);
    mfree(pi);
    printf("%p\n", *freep);

    return 0;
}


/* mmalloc: general-purpose storage allocator */
void *mmalloc(size_t nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {          /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {

        if (p->s.size >= nunits) {          /* big enough */
            if (p->s.size == nunits)        /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {                          /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }

        if (p == freep)                     /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL;                /* none left */
    }
}


/* morecore: ask system for more memory */
static Header *morecore(size_t nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = (char *) sbrk(nu * sizeof(Header));

    if (cp == (char *) -1)                  /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;
    mfree((void *)(up+1));

    return freep;
}


/* mfree: put block ap in free list */
void mfree(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;                  /* point to block header */

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            /* freed block at start or end of arena */
            break;

    if (bp + bp->s.size == p->s.ptr) {        /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {                /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;

    freep = p;
}
