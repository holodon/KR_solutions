/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x . Explain why. Use this observation to write a faster version of bitcount .

when x is for example:
	10101010	or  other example 10101111
then x-1 looks like
	10101001	or                10101110
or we could say the (x-1) operation moves the right most '1' one bit to the right
then if we compute x &= (x-1) everything is the same except the last '1' and the 
following '0' which gets 'removed'
*/

#include <stdio.h>

int bitcount(unsigned x);
void printBits(size_t const size, void const * const ptr);

int main(void)
{
	unsigned int x;
	x = 0b10101111;
	printf("x            : ");
	printBits(sizeof(x), &x);
	printf("count of 1's : %d\n", bitcount(x));

	return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b = 0;
	while (x) {
		x &= (x - 1);
		b++;
	}
	return b;
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
