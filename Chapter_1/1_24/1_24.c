/*
Exercise 1-24. Write a program to check a C program for rudimentary syntax errors like
unmatched parentheses, brackets and braces. Don't forget about quotes, both single and
double, escape sequences, and comments. (This program is hard if you do it in full
generality.)

Build on top of 1_23 - a state machine for skipping quotes and special symbols.
*/

#include <stdio.h>

void filLineList(int c);
void parseList();

/*
 keep track of lines and col's:
*/
int line = 1;
int col = 0;

#define MAX 1000
#define ROW 4
#define lLine 0									// line
#define lCol 1									// column
#define lType 2									// type
#define lNext 3									// next

/* 
 structure (array as linked list) for the parentheses, brackets and braces like:
	{line, col, type, next},
	{line, col, type, next},
	...
*/
int list[MAX][ROW];

int pos = 0;									// current position in list

int main(void)
{
	// initialize the list array
	for (int i = 0; i < MAX; i++) {
		list[i][lLine] = -1;
		list[i][lCol] = -1;
		list[i][lType] = -1;
		list[i][lNext] = -1;
	}


	int state = 0;		/* states: 
							0 - none;

						single row comment:
							1 - "/"; 2 - "//"

						multiline comment:
							3 - "/*"; 4 - "/* .. *"
						*/
	int c = 0;
	int sQuotes = 0;							// single quotes
	int dQuotes = 0;							// double quotes
	int skipping = 0;							// skipping modus (comment body)
	int special = 0;							// backslash

	while((c = getchar()) != EOF) {

		if (pos == MAX) {						// overflow check
			printf("Too much elements to parse - recompile with bigger MAX!\nExiting.\n\n");
			return -1;
		}

		if (c == '\n') {
			col = 1;
			line++;
		} else
			col++;

		if (!skipping)  {
			if (special) {						// backslash
				filLineList(c);
				special = 0;
				continue;
			}

			if (c == '\\') {					// char after backslash
				filLineList(c);
				special = 1;
				continue;
			}

			if (c == '"' && !sQuotes)			// double quote
				dQuotes = (dQuotes == 0)? 1:0;
			else if (c == '\'' && !dQuotes)		// single quote
				sQuotes = (sQuotes == 0)? 1:0;

			if (sQuotes || dQuotes) {			// skip everything in the quotes
				continue;
			}
		}

		switch (state) {
			case 0:								// no state
				if (c == '/')
					state = 1;
				else
					filLineList(c);
				break;

			case 1:								// "/" state
				if (c == '/') {
					skipping = 1;
					state = 2;
				}
				else if (c == '*') {
					skipping = 1;
					state = 3;
				}
				else {
					filLineList('/');			// corner case
					filLineList(c);
					skipping = 0;
					state = 0;
				}
				break;

			case 2:
				if (c == '\n') {				// end of line comment
					filLineList('\n');
					skipping = 0;
					state = 0;
				}
				else
					;							// or continue skipping
				break;

			case 3:								// "/*" state
				if (c == '*')
					state = 4;
				else
					;							// or continue skipping
				break;

			case 4:								// "/* .. *"
				if (c == '/') {					// end of multiline comment
					skipping = 0;
					state = 0;
				}
				else
					state = 3;					// or continue skipping
				break;

		}

	}

	parseList();
	printf("\nDone!\n\n");

	return 0;
}

/*
	This function receives each char which is not a special character, or not in a 
	quote. Then it fills the array "list" with every parentheses, brackets and braces
	found, in the correct sequence.
*/
void filLineList(int c)
{
	if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
		list[pos][lLine] = line;
		list[pos][lCol] = col -1;
		list[pos][lType] = c;
		list[pos][lNext] = -1;
		list[pos-1][lNext] = pos;
		pos ++;
	}
}

/*
	This function parses the array "list" over and over again until there are no changes
	to be made. By each cycle it removes matching parentheses, brackets and braces.
	At the end it shows each of the remaining elements, i.e. elements without match.
*/
void parseList()
{
	/*
	 corner cases:
	*/
	if (list[0][0] == -1)						// empty list
		return;

	if (pos == 1) {								// list with only one element
		printf("Unmatched %c at line %d col %d\n", 
			list[0][lType], list[0][lLine], list[0][lCol]);
		return;
	}

	int change = 1;								// change during parsing the list
	int done = 0;								// done =1 after a full cycle without change
	int head = 0;								// start of the list
	pos = 0;									// current position
	int last = -1;								// the last position

	do {
		if ( 	(list [pos][lType] == '(' && list [list[pos][lNext]] [lType] == ')') ||
				(list [pos][lType] == '[' && list [list[pos][lNext]] [lType] == ']') ||
				(list [pos][lType] == '{' && list [list[pos][lNext]] [lType] == '}') ) 
		{

			change =1;

			if (pos == head) {					// move the head if needed
				if (list [ list[pos][lNext] ] [lNext] == -1) {
					printf("All good...\n");	// the last two elements removed
					return;
				}
				head = list [ list[pos][lNext] ] [lNext];
			}

												// "remove" the two matching elements
			list [last][lNext] = list [list[pos][lNext]] [lNext];
		}

		last = pos;								/* save the current (last) position 
												 and advance */

		if (list [pos][lNext] == -1) {			// end of list reached - start over
			pos = head;
			last = -1;
			if (!change)
				done = 1;
			else
				change = 0;
		} else
			pos = list[pos][lNext];		

	} while (!done);

												// print all errors
	pos = head;
	while (1) {
		printf("Unmatched %c at line %d col %d\n", 
			list[pos][lType], list[pos][lLine], list[pos][lCol]);
		if (list [pos] [lNext] == -1) {
			break;
		}
		pos = list[pos][lNext];
	}
}