/*
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/

#include <stdio.h>

int invert(unsigned x, int p, int n);
void printBits(size_t const size, void const * const ptr);

int main(void)
{

	unsigned int x;
	int p, n;
	x = 0b01010101;
	p = 5;
	n = 2;

	unsigned r = invert(x, p, n);
	printBits(sizeof(x), &x);
	printBits(sizeof(r), &r);


	return 0;
}

int invert(unsigned x, int p, int n)
{
	unsigned int mask = ~(~0 << (p - n)) << (p - n);
	return ~(x & mask) ^ ~mask | (x & ~mask);
}

// print binary
// https://stackoverflow.com/a/3974138/6049386
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
