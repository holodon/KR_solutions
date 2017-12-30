/*
Exercise 8-6. The standard library function calloc(n,size) returns a pointer to
n objects of size size , with the storage initialized to zero. Write calloc ,
by calling malloc or by modifying it.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5               /* count of elements to allocate */
void *mcalloc(size_t, size_t);

int main(void)
{
    long *pt, *tmp;
    int i, c;


    if ((pt = mcalloc(MAX, sizeof(long))) == NULL)
        return -1;                          /* memory error */

    printf("result from mcalloc:\n");
    printf("\t   adress    value\n");
    printf("\t-------------------\n");
    tmp = pt;
    for (i = 0; i < MAX; i++)
        printf("\t%10p: %08ld\n", tmp, *tmp++);

    free(pt);

    return 0;
}

/* allocate memory and initialize it to zeros */
void *mcalloc(size_t n, size_t size)
{
    size_t s, i;
    s = n * size;

    char *res, *tmp;                        /* char choosen as the smallest */
                                            /* data type, meaning */
                                            /* sizeof(char) = 1 byte <= size */
    res = tmp = malloc(s);
    if (res != NULL)
        for (i = 0; i < s; i++)
            *tmp++ = 0;

    return res;
}
