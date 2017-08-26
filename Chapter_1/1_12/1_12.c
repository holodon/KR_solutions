/*
Exercise 1-12. Write a program that prints its input 
one word per line.
*/

#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* print the input one word per line */
/* test file included - use it like:
	cat test | ./a.out */
int main(void) {
	int c;
	int newline = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (!newline) {
				putchar('\n');
				newline = 1;
			}
		} else {
			putchar(c);
			newline = 0;
		}
	}
	printf("\n");
}
