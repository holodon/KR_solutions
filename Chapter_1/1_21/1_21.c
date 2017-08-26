/*
Exercise 1-21. Write a program entab that replaces strings of blanks
by the minimum number of tabs and blanks to achieve the same spacing.
Use the same tab stops as for detab . When either a tab or a single 
blank would suffice to reach a tab stop, which should be given
preference?
*/

#include <stdio.h>

int main(void)
{
	int c;
	int col = 0;	// column counter
	int tab = 8;	// tab size	[0..7]
	int sp = 0;		// space counter

	while((c = getchar()) != EOF) {
		if (c == '\n') {
			putchar(c);
			col = 0;
		} else if (c == ' ') {				// space
			sp++;
			if ((col + sp) % tab == 0) {	// tab possible?
				putchar('\t');
				sp = 0;
				col = 0;
			}

		} else {							// everything else
			if (sp > 0) {					// print buffered spaces if any
				for (int i = 0; i < sp; i++) {
					//putchar('_');			// for testing/easier visualisation
					putchar(' ');
					col++;
				}
				sp = 0;
			}
			putchar(c);						// default print char
			col++;
		}
	}
	return 0;
}
