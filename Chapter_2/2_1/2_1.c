/*
Exercise 2-1. Write a program to determine the ranges of char , short , int , and long
variables, both signed and unsigned , by printing appropriate values from standard headers
and by direct computation. Harder if you compute them: determine the ranges of the various
floating-point types.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
	printf("Limits:\n");

	printf("bits in a char:                 %d\n", CHAR_BIT);

	printf("maximum value of a char:        %d\n", CHAR_MAX);
	printf("minimum calue of a char:        %d\n", CHAR_MIN);

	printf("maximum value of int:           %d\n", INT_MAX);
	printf("minimum value of int:           %d\n", INT_MIN);

	printf("maximum value of long:          %ld\n", LONG_MAX);
	printf("minimum value of long:          %ld\n", LONG_MIN);

	printf("maximum value of signed char:   %d\n", SCHAR_MAX);
	printf("minimum value of signed char:   %d\n", SCHAR_MIN);

	printf("maximum value of short:         %d\n", SHRT_MAX);
	printf("minimum value of short:         %d\n", SHRT_MIN);

	printf("maximum value of unsigned char: %d\n", UCHAR_MAX);

	printf("maximum value of unsigned int:  %u\n", UINT_MAX);

	printf("minimum value of unsigned long: %lu\n\n", ULONG_MAX);

	printf("smallest number x such that 1.0+x != 1.0: %.30lf\n", FLT_EPSILON);

	return 0;
}