/*
Exercise 1-22. Write a program to "fold" long input lines into two or more shorter lines after
the last non-blank character that occurs before the n-th column of input. Make sure your
program does something intelligent with very long lines, and if there are no blanks or tabs
before the specified column.
*/

#include <stdio.h>
#define MAX 20					// max line-length

void mprint(int start, int max, int buff[]);
void shift(int start, int max, int buff[]);

int main(void)
{
	int col = 0;				// column counter
	int sp = -1;				// position of the last space/tab (-1 => none so far)
	int buff[MAX];				// string buffer

	while((buff[col] = getchar()) != EOF) {

		if (buff[col] == '\n') {			// newline - do not fold anything
			mprint(0, col + 1, buff);
			sp = -1;
			col = 0;
			continue;
		}

		if (buff[col] == ' ' || buff[col] == '\t') {
			sp = col;						// save the last space/tab position
		}

		col++;

		if (col == MAX) {					// time to fold

			if (sp == -1) {					// no space/tab on the row
				mprint(0, MAX, buff);
				putchar('\n');
				col = 0;
				sp = -1;
			} else {						// space/tab found
				//mprint(0, sp + 1, buff);	// print with trailing space
				mprint(0, sp, buff);		// print w/o trailing space
				putchar('\n');
				shift(sp + 1, MAX, buff);
				col = MAX - sp - 1;
				sp = -1;
			}

		}

	}

	return 0;
}

// prints a part of array
void mprint(int start, int max, int buff[])
{
	int i;
	for (i = start; i < max; i++) {
		putchar(buff[i]);
	}
}

// shift elements of a array to its start
void shift(int start, int max, int buff[])
{
	int i;
	int p = 0;
	for (i = start; i < max; i++) {
		buff[p] = buff[i];
		p++;
	}
}
