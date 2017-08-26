/*
Exercise 1-10. Write a program to copy its input to its output, 
replacing each tab by \t , each backspace by \b , and each 
backslash by \\ . This makes tabs and backspaces visible in an
unambiguous way.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int c;

	/* for the \b to get registered we have to modify the
		terminal behaviour - OS and terminal dependent -
		to not buffer */
	// system ("/bin/stty raw");

	while ((c = getchar()) != EOF) {
		if (c == '\b') {
			putchar('\\');
			putchar('b');
		} else if (c == '\t') {
			putchar('\\');
			putchar('t');
		} else if (c == '\\') {
			putchar('\\');
		} else {
			putchar(c);
		}
	}
	printf("\n");

	// system ("/bin/stty cooked");
}