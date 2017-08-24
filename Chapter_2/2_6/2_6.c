/*
Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y , leaving the other bits unchanged.
*/

#include <stdio.h>

int setbits(unsigned x, int p, int n, unsigned y);
void printBits(size_t const size, void const * const ptr);

int main(void)
{

	unsigned int x, y;
	int p, n;
	x = 0b11111111;
	y = 0b10101000;

	int res = setbits(x, 4, 2, y);

	printBits(sizeof(res), &res);
	return 0;
}

int setbits(unsigned x, int p, int n, unsigned y)
{
		// mask x         wide enough mask like 11110011    last n bits from y shifted to p like 0000xx00
	return x     &    (~0 << (p + 1) | ~(~0 << (p - n + 1)))   |   ((~(~0 << n) & y) << (p - n + 1));
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