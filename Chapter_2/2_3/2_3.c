/*
Exercise 2-3. Write a function htoi(s) , which converts a string of 
hexadecimal digits (including an optional 0x or 0X ) into its equivalent 
integer value. The allowable digits are 0 through 9 , a through f , and A 
through F.

This program is limited to the range of int (as far as the excerice goes).
$ gcc -lm 2_3.c
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>

int htoi(char s[]);
int hexToDec(char c);

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;

	printf("%d\n", htoi(argv[1]));
	return 0;
}

int htoi(char s[])
{
	int n = 0;
	int start = 0;

	// get length
	int len = 0;
	while (s[len])
		len++;

	// get starting position
	if (len > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		start = 2;

	// calculate
	int i, k;
	for (i = len - 1; i >= start; i--) {
		if ((k = hexToDec(s[i])) == -1)
			return -1;
		n += k * pow(16, len - i - 1);
	}

	return n;
}

int hexToDec(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';

	c = tolower(c);
	if (c >= 'a' && c <= 'f')
		return c + 10 - 'a';

	// wrong char
	return -1;
}