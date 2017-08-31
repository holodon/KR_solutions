/*
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits 
that begin at position p inverted (i.e., 1 changed into 0 and vice versa), 
leaving the others unchanged.
*/

#include <stdio.h>
#include <limits.h>

int invert(unsigned x, int p, int n);
void printBits(size_t const size, void const * const ptr);

int main(void)
{

	unsigned int x;
	int p, n;
	x = 0b01010101;
	p = 7;
	n = 3;

	int r = invert(x, p, n);
    printf("original: \n");
	printBits(sizeof(x), &x);
    printf("after invert: \n");
	printBits(sizeof(r), &r);

	return 0;   
}

int invert(unsigned x, int p, int n)
{
    int sz = sizeof(x) * CHAR_BIT;
    if ((n > (p + 1)) | (p >= sz)) {
        printf("invalid argument/s\n");
        return 0;
    }

	unsigned int mask;
    mask = (n == sz)
        ? ~0
        : (~(~0 << n) << (p - n + 1));
    printf("mask: \n");
    printBits(sizeof(mask), &mask);
    printf("\n");

	return ~(x & mask) ^ ~mask | (x & ~mask);
}

// print binary
// https://stackoverflow.com/a/3974138/6049386
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
