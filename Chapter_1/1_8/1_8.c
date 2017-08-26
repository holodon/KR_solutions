/*
Exercise 1-8. Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>
/* count blanks, tabs and newlines in input */
int main(void) {
	int c, nl;
	nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			++nl;
		}
	}
	printf("%d\n", nl);
}
